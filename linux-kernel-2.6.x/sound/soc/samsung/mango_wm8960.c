/*
 * mango24_wm8960.c
 *
 * Copyright (C) 2010 Samsung Electronics Co.Ltd
 * Author: Chanwoo Choi <cw00.choi@samsung.com>
 *
 *  This program is free software; you can redistribute  it and/or modify it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 *
 */

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/io.h>
#include <linux/clk.h>
#include <linux/platform_device.h>

#include <sound/soc.h>
#include <sound/jack.h>
#include <sound/pcm_params.h>

#include <asm/mach-types.h>
#include <mach/gpio.h>
#include <mach/regs-clock.h>

#include "../codecs/wm8960.h"
#include "dma.h"
#include "i2s.h"

static struct snd_soc_card mango24;
static struct platform_device *mango24_snd_device;

/* 3.5 pie jack */
static struct snd_soc_jack jack;

/* 3.5 pie jack detection DAPM pins */
static struct snd_soc_jack_pin jack_pins[] = {
        {
                .pin = "Headphone Jack",
                .mask = SND_JACK_HEADPHONE | SND_JACK_MECHANICAL |
                        SND_JACK_LINEOUT,
        },
};

/* 3.5 pie jack detection gpios */
static struct snd_soc_jack_gpio jack_gpios[] = {
	{
		.gpio = S3C2410_GPG(6),
		.name = "headphone detect",
		.report = SND_JACK_HEADSET | SND_JACK_MECHANICAL |
			SND_JACK_LINEOUT,
		.invert = 1,
		.debounce_time = 200,
	},
};

static const struct snd_soc_dapm_widget mango24_dapm_widgets[] = {
        SND_SOC_DAPM_HP("Headphone Jack", NULL),
        SND_SOC_DAPM_SPK("Internal Speaker", NULL),
        SND_SOC_DAPM_MIC("Internal Mic", NULL),
        SND_SOC_DAPM_MIC("LineIn", NULL),
};

static const struct snd_soc_dapm_route mango24_dapm_routes[] = {
        /* MicIn feeds AINL */
        {"LINPUT1", NULL, "Internal Mic"},
        {"LINPUT2", NULL, "Internal Mic"},
        {"LINPUT3", NULL, "LineIn"},
        {"RINPUT3", NULL, "LineIn"},
        {"Headphone Jack",      NULL,   "HP_L" },
        {"Headphone Jack",      NULL,   "HP_R" },

        {"Internal Speaker",            NULL,   "SPK_LP"},
        {"Internal Speaker",            NULL,   "SPK_RP"},
        {"Internal Speaker",            NULL,   "SPK_LN"},
        {"Internal Speaker",            NULL,   "SPK_RN"},

};

static int mango24_wm8960_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_codec *codec = rtd->codec;
	struct snd_soc_dapm_context *dapm = &codec->dapm;
	int ret;

	/* add mango24 specific widgets */
	snd_soc_dapm_new_controls(dapm, mango24_dapm_widgets,
			ARRAY_SIZE(mango24_dapm_widgets));

	/* set up mango24 specific audio routes */
	snd_soc_dapm_add_routes(dapm, mango24_dapm_routes,
			ARRAY_SIZE(mango24_dapm_routes));

	/* set endpoints to not connected */
        snd_soc_dapm_new_widgets(dapm);
        snd_soc_dapm_enable_pin(dapm, "Internal Mic");
        snd_soc_dapm_enable_pin(dapm, "Internal Speaker");
        snd_soc_dapm_disable_pin(dapm, "Headphone Jack");

	snd_soc_dapm_sync(dapm);
#if 1
	/* Headset jack detection */
	ret = snd_soc_jack_new(codec, "Headset Jack",
			SND_JACK_HEADSET | SND_JACK_MECHANICAL | SND_JACK_AVOUT,
			&jack);
	if (ret)
		return ret;

	ret = snd_soc_jack_add_pins(&jack, ARRAY_SIZE(jack_pins), jack_pins);
	if (ret)
		return ret;

	ret = snd_soc_jack_add_gpios(&jack, ARRAY_SIZE(jack_gpios), jack_gpios);
	if (ret)
		return ret;
#endif
	return 0;
}

static int set_epll_rate(unsigned long rate)
{
        struct clk *fout_epll;

        fout_epll = clk_get(NULL, "i2s_eplldiv");
        if (IS_ERR(fout_epll)) {
                printk(KERN_ERR "%s: failed to get fout_epll\n", __func__);
                return -ENOENT;
        }

        if (rate == clk_get_rate(fout_epll))
                goto out;

        clk_set_rate(fout_epll, rate);
out:
        clk_put(fout_epll);

        return 0;
}

static int mango24_hifi_hw_params(struct snd_pcm_substream *substream,
		struct snd_pcm_hw_params *params)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai *codec_dai = rtd->codec_dai;
	struct snd_soc_dai *cpu_dai = rtd->cpu_dai;

        unsigned int rclk = 0;
        unsigned int bfs, psr, rfs, ret = 0;

printk("start hw_params\n");
        switch (params_format(params)) {
        case SNDRV_PCM_FORMAT_U24:
        case SNDRV_PCM_FORMAT_S24:
                bfs = 48;
                break;
        case SNDRV_PCM_FORMAT_U16_LE:
        case SNDRV_PCM_FORMAT_S16_LE:
                bfs = 32;
                break;
        default:
                return -EINVAL;
        }

        switch (params_rate(params)) {
        case 16000:
        case 22050:
        case 24000:
        case 32000:
        case 44100:
        case 48000:
        case 88200:
        case 96000:
                if (bfs == 48)
                        rfs = 384;
                else
                        rfs = 256;
                break;
        case 64000:
                rfs = 384;
                break;
        case 8000:
        case 11025:
        case 12000:
                if (bfs == 48)
                        rfs = 768;
                else
                        rfs = 512;
                break;
        default:
                return -EINVAL;
        }

        rclk = params_rate(params) * rfs;

        switch (rclk) {
        case 4096000:
        case 5644800:
        case 6144000:
        case 8467200:
        case 9216000:
                psr = 8;
                break;
        case 8192000:
        case 11289600:
        case 12288000:
        case 16934400:
        case 18432000:
                psr = 4;
                break;
        case 22579200:
        case 24576000:
        case 33868800:
        case 36864000:
                psr = 2;
                break;
        case 67737600:
        case 73728000:
                psr = 1;
                break;
        default:
                printk("Not yet supported!\n");
                return -EINVAL;
        }

        set_epll_rate(rclk * psr);

	/* set the cpu DAI configuration */
	ret = snd_soc_dai_set_fmt(cpu_dai, SND_SOC_DAIFMT_I2S |
			SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_CBS_CFS);
	if (ret < 0)
		return ret;

	/* set codec DAI configuration */
	ret = snd_soc_dai_set_fmt(codec_dai, SND_SOC_DAIFMT_I2S |
			SND_SOC_DAIFMT_NB_NF | SND_SOC_DAIFMT_CBS_CFS);
	if (ret < 0)
		return ret;

        /* Use PCLK for I2S signal generation */
        ret = snd_soc_dai_set_sysclk(cpu_dai, SAMSUNG_I2S_RCLKSRC_0,
                                        0, SND_SOC_CLOCK_IN);
        if (ret < 0)
                return ret;

        /* Gate the RCLK output on PAD */
        ret = snd_soc_dai_set_sysclk(cpu_dai, SAMSUNG_I2S_CDCLK,
                                        0, SND_SOC_CLOCK_OUT);
        if (ret < 0)
                return ret;

#if 1
        ret = snd_soc_dai_set_clkdiv(cpu_dai, SAMSUNG_I2S_DIV_BCLK, bfs);
        if (ret < 0)
                return ret;

#endif

printk("stop hw_params\n");

	return 0;
}

static struct snd_soc_ops mango24_hifi_ops = {
	.hw_params = mango24_hifi_hw_params,
};

static struct snd_soc_dai_link mango24_dai[] = {
{
	.name = "WM8960",
	.stream_name = "Playback",
	.cpu_dai_name = "samsung-i2s",
	.codec_dai_name = "wm8960-hifi",
	.platform_name = "samsung-audio",
	.codec_name = "wm8960-codec.0-001a",
	.init = mango24_wm8960_init,
	.ops = &mango24_hifi_ops,
},
};

static struct snd_soc_card mango24 = {
	.name = "SMDK-I2S",
	.dai_link = mango24_dai,
	.num_links = ARRAY_SIZE(mango24_dai),
};

#if 1
static int __init mango24_init(void)
{
	int ret;

	printk("Mango 24 Audio Support\n");
	mango24_snd_device = platform_device_alloc("soc-audio", -1);
	if (!mango24_snd_device)
		return -ENOMEM;

	platform_set_drvdata(mango24_snd_device, &mango24);
	ret = platform_device_add(mango24_snd_device);

	if (ret) {
		snd_soc_unregister_dai(&mango24_snd_device->dev);
		platform_device_put(mango24_snd_device);
	}

	return ret;
}

static void __exit mango24_exit(void)
{
	snd_soc_unregister_dai(&mango24_snd_device->dev);
	platform_device_unregister(mango24_snd_device);
}

module_init(mango24_init);
module_exit(mango24_exit);
#endif

/* Module information */
MODULE_DESCRIPTION("ALSA SoC WM8960 MANGO24(S3C2450)");
MODULE_AUTHOR("Chanwoo Choi <cw00.choi@samsung.com>");
MODULE_LICENSE("GPL");
