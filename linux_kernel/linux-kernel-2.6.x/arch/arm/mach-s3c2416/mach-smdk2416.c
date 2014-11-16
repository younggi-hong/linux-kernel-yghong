/* linux/arch/arm/mach-s3c2416/mach-hanlin_v3c.c
 *
 * Copyright (c) 2009 Yauhen Kharuzhy <jekhor@gmail.com>,
 *	as part of OpenInkpot project
 * Copyright (c) 2009 Promwad Innovation Company
 *	Yauhen Kharuzhy <yauhen.kharuzhy@promwad.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
*/

#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/list.h>
#include <linux/timer.h>
#include <linux/init.h>
#include <linux/serial_core.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/mtd/mtd.h>
#include <linux/mtd/nand.h>
#include <linux/mtd/nand_ecc.h>
#include <linux/mtd/partitions.h>
#include <linux/gpio.h>
#include <linux/fb.h>
#include <linux/smsc911x.h>
#include <linux/gpio_keys.h>
#include <linux/leds.h>
#include <linux/input.h>
#include <linux/delay.h>
#include <linux/usb/gpio_vbus.h>

#include <asm/mach/arch.h>
#include <asm/mach/map.h>
#include <asm/mach/irq.h>

#include <mach/hardware.h>
#include <asm/irq.h>
#include <asm/mach-types.h>

#include <video/platform_lcd.h>

#include <plat/regs-serial.h>
#include <mach/regs-gpio.h>
#include <mach/regs-lcd.h>
#include <mach/regs-s3c2412-mem.h>

#include <mach/idle.h>
#include <mach/leds-gpio.h>
#include <plat/iic.h>

#include <plat/s3c2416.h>
#include <plat/adc.h>
#include <plat/gpio-cfg.h>
#include <plat/clock.h>
#include <plat/devs.h>
#include <plat/cpu.h>
#include <plat/nand.h>
#include <plat/sdhci.h>
#include <plat/ts.h>
#include <plat/udc.h>
#include <plat/pm.h>

#include <plat/regs-fb-v4.h>
#include <plat/fb.h>

#include <plat/common-smdk.h>

static struct map_desc smdk2416_iodesc[] __initdata = {
	{
		.virtual	= (u32)S3C2416_VA_SMSC9220,
		.pfn		= __phys_to_pfn(S3C2410_CS5),
		.length		= SZ_4M,
		.type		= MT_DEVICE,
	}
};

#define UCON (S3C2410_UCON_DEFAULT	| \
		S3C2440_UCON_PCLK	| \
		S3C2443_UCON_RXERR_IRQEN)

#define ULCON (S3C2410_LCON_CS8 | S3C2410_LCON_PNONE)

#define UFCON (S3C2410_UFCON_RXTRIG8	| \
		S3C2410_UFCON_FIFOMODE	| \
		S3C2440_UFCON_TXTRIG16)

static struct s3c2410_uartcfg smdk2416_uartcfgs[] __initdata = {
	[0] = {
		.hwport	     = 0,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
	},
	[1] = {
		.hwport	     = 1,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
	},
	/* IR port */
	[2] = {
		.hwport	     = 2,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON | 0x50,
		.ufcon	     = UFCON,
	},
	[3] = {
		.hwport	     = 3,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
	}
};

static struct gpio_keys_button mango24_gpio_keys_table[] = {
        {
                .code           = KEY_POWER,
                .gpio           = S3C2410_GPF(0),
                .desc           = "gpio-keys: KEY_POWER",
                .type           = EV_KEY,
                .active_low     = 1,
                // .wakeup         = 1,
                .debounce_interval = 5,
        },
        {
                .code           = KEY_MENU,
                .gpio           = S3C2410_GPF(1),
                .desc           = "gpio-keys: KEY_MENU",
                .type           = EV_KEY,
                .active_low     = 1,
                // .wakeup         = 1,
                .debounce_interval = 5,
        },
};

static struct gpio_keys_platform_data mango24_gpio_keys_data = {
        .buttons        = mango24_gpio_keys_table,
        .nbuttons       = ARRAY_SIZE(mango24_gpio_keys_table),
        .poll_interval  = 200,
};

static struct platform_device mango24_device_gpiokeys = {
        .name = "gpio-keys-polled",
        .dev = {
                .platform_data = &mango24_gpio_keys_data,
        },
};

static struct resource mango24_smsc911x_resources[] = {
        [0] = {
                .start = S3C2410_CS5,
                .end   = S3C2410_CS5 + SZ_64K - 1,
                .flags = IORESOURCE_MEM,
        },
        [1] = {
                .start = IRQ_EINT13,
                .end   = IRQ_EINT13,
                .flags = IORESOURCE_IRQ | IRQ_TYPE_LEVEL_LOW,
        },
};

static struct smsc911x_platform_config mango24_smsc911x_pdata = {
        .irq_polarity  = SMSC911X_IRQ_POLARITY_ACTIVE_LOW,
        .irq_type      = SMSC911X_IRQ_TYPE_PUSH_PULL,
        .flags         = SMSC911X_USE_16BIT | SMSC911X_FORCE_INTERNAL_PHY,
        .phy_interface = PHY_INTERFACE_MODE_MII,
        .mac           = {0x00, 0x80, 0x00, 0x23, 0x45, 0x67},
};


static struct platform_device mango24_smsc911x = {
        .name          = "smsc911x",
        .id            = -1,
        .num_resources = ARRAY_SIZE(mango24_smsc911x_resources),
        .resource      = &mango24_smsc911x_resources[0],
        .dev = {
                .platform_data = &mango24_smsc911x_pdata,
        },
};

/* NAND parititon from 2.4.18-swl5 */

static struct mtd_partition smdk_default_nand_part[] = {
        [0] = {
                .name           = "Bootloader",
                .offset         = 0,
                .size           = (256*SZ_1K),
                .mask_flags     = MTD_CAP_NANDFLASH,
        },
        [1] = {
                .name           = "Kernel",
                .offset         = (256*SZ_1K),    /* Block number is 0x10 */
                .size           = (4*SZ_1M) - (256*SZ_1K),
                .mask_flags     = MTD_CAP_NANDFLASH,
        },
        [2] = {
                .name           = "rootfs",
                .offset         = MTDPART_OFS_APPEND,
                .size           = MTDPART_SIZ_FULL,
        },
};

static struct s3c2410_nand_set smdk_nand_sets[] = {
        [0] = {
                .name           = "NAND",
                .nr_chips       = 1,
                .nr_partitions  = ARRAY_SIZE(smdk_default_nand_part),
                .partitions     = smdk_default_nand_part,
        },
};

/* choose a set of timings which should suit most 512Mbit
 * chips and beyond.
*/

static struct s3c2410_platform_nand smdk_nand_info = {
        .tacls          = 20,
        .twrph0         = 60,
        .twrph1         = 20,
        .nr_sets        = ARRAY_SIZE(smdk_nand_sets),
        .sets           = smdk_nand_sets,
};

struct s3c_fb_pd_win smdk2416_fb_win[] = {
	[0] = { /* LG LB070WV6 */
		.win_mode	= {
			.pixclock	= 42000,
			.left_margin	= 64,
			.right_margin	= 64,
			.upper_margin	= 16,
			.lower_margin	= 14,
			.hsync_len	= 128,
			.vsync_len	= 1,
			.xres           = 800,
			.yres           = 480,
		},
		.default_bpp	= 24,
		.max_bpp	= 32,
	},
};

static void s3c2416_fb_gpio_setup_24bpp(void)
{
	unsigned int gpio;

	for (gpio = S3C2410_GPC(1); gpio <= S3C2410_GPC(4); gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
	}

	for (gpio = S3C2410_GPC(8); gpio <= S3C2410_GPC(15); gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
	}

	for (gpio = S3C2410_GPD(0); gpio <= S3C2410_GPD(15); gpio++) {
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
	}
}

static struct s3c_fb_platdata smdk2416_fb_platdata = {
	.win[0]		= &smdk2416_fb_win[0],
	.setup_gpio	= s3c2416_fb_gpio_setup_24bpp,
	.vidcon0	= VIDCON0_VIDOUT_RGB_2443 | VIDCON0_PNRMODE_BGR_2443,
	.vidcon1	= VIDCON1_INV_HSYNC | VIDCON1_INV_VSYNC,
};

static struct s3c_sdhci_platdata smdk2416_hsmmc0_pdata __initdata = {
	.max_width		= 4,
	.cd_type		= S3C_SDHCI_CD_GPIO,
	.ext_cd_gpio		= S3C2410_GPG(3),
	.ext_cd_gpio_invert	= 1,
#if 0
	.cd_type		= S3C_SDHCI_CD_GPIO,
	.ext_cd_gpio		= S3C2410_GPF(1),
	.ext_cd_gpio_invert	= 1,
#endif
};

static struct s3c_sdhci_platdata smdk2416_hsmmc1_pdata __initdata = {
	.max_width		= 4,
	.cd_type		= S3C_SDHCI_CD_INTERNAL,
#if 0
	.cd_type		= S3C_SDHCI_CD_GPIO,
	.ext_cd_gpio		= S3C2410_GPG(3),
	.ext_cd_gpio_invert	= 1,
#endif
};

static struct gpio_led mango24_leds[] = {
        { 
                .name                   = "LED0",
                .gpio                   = S3C2410_GPF(2),
                .default_trigger        = "default-on",
		.active_low 		= 1,
        },
        { 
                .name                   = "LED1",
                .gpio                   = S3C2410_GPF(3),
                .default_trigger        = "heartbeat",
		.active_low 		= 1,
        },
};

static struct gpio_led_platform_data mango24_led_data = {
        .num_leds = ARRAY_SIZE(mango24_leds),
        .leds = mango24_leds,
};

static struct platform_device mango24_leds_device = {
        .name                   = "leds-gpio",
        .id                     = -1,
        .dev.platform_data      = &mango24_led_data,
};

static struct i2c_board_info mango24_i2c0_board_info[] __initdata = {
        {
                I2C_BOARD_INFO("wm8960", 0x1a),
        }
};

static void mango24_lb070wv6_set_power(struct plat_lcd_data *pd,
                                        unsigned int power)
{
        if (power) {
#if !defined(CONFIG_BACKLIGHT_PWM)
                gpio_request(S3C2410_GPB(3), "Display Backlight");
                gpio_direction_output(S3C2410_GPB(3), 1);
                gpio_free(S3C2410_GPB(3));
#endif

                /* LCD POWER Enable */
                gpio_request(S3C2410_GPG(4), "Display POWER");
                gpio_direction_output(S3C2410_GPG(4), 1);
                gpio_free(S3C2410_GPG(4));
        } else {
#if !defined(CONFIG_BACKLIGHT_PWM)
                gpio_request(S3C2410_GPB(3), "Display Backlight");
                gpio_direction_output(S3C2410_GPB(3), 0);
                gpio_free(S3C2410_GPB(3));
#endif
        }
}

static struct plat_lcd_data mango24_lcd_lb070wv6_data = {
        .set_power      = mango24_lb070wv6_set_power,
};

static struct platform_device mango24_lcd_lb070wv6 = {
        .name                   = "platform-lcd",
        .dev.parent             = &s3c_device_fb.dev,
        .dev.platform_data      = &mango24_lcd_lb070wv6_data,
};

static struct s3c2410_ts_mach_info s3c_ts_platform __initdata = {
        .delay                  = 10000,
        .presc                  = 49,
        .oversampling_shift     = 2,
};

void smdk2416_hsudc_gpio_init(void)
{
        s3c_gpio_setpull(S3C2410_GPH(14), S3C_GPIO_PULL_UP);
        s3c_gpio_setpull(S3C2410_GPG(10), S3C_GPIO_PULL_NONE);
        s3c_gpio_cfgpin(S3C2410_GPH(14), S3C_GPIO_SFN(1));
        s3c2410_modify_misccr(S3C2416_MISCCR_SEL_SUSPND, 0);
}

void smdk2416_hsudc_gpio_uninit(void)
{
        s3c2410_modify_misccr(S3C2416_MISCCR_SEL_SUSPND, 1);
        s3c_gpio_setpull(S3C2410_GPH(14), S3C_GPIO_PULL_NONE);
        s3c_gpio_cfgpin(S3C2410_GPH(14), S3C_GPIO_SFN(0));
}

struct s3c24xx_hsudc_platdata smdk2416_hsudc_platdata = {
        .epnum = 9,
        .gpio_init = smdk2416_hsudc_gpio_init,
        .gpio_uninit = smdk2416_hsudc_gpio_uninit,
};

static struct gpio_vbus_mach_info mango24_hsudc_vbus_pdata = {
        .gpio_vbus              = S3C2410_GPG(10),
        .gpio_pullup            = -1,
        .gpio_vbus_inverted     = true,
};

static struct platform_device mango24_hsudc_vbus_dev = {
        .name                   = "gpio-vbus",
        .dev.platform_data      = &mango24_hsudc_vbus_pdata,
};

static struct platform_device *smdk2416_devices[] __initdata = {
        &s3c_device_adc,
	&s3c_device_fb,
	&s3c_device_wdt,
	&s3c_device_rtc,
	&s3c_device_nand,
	&s3c_device_ohci,
        &s3c_device_ts,
	&s3c_device_i2c0,
	&s3c2416_device_iis,
	&samsung_asoc_dma,
	&s3c_device_hsmmc0,
	&s3c_device_hsmmc1,
	&mango24_hsudc_vbus_dev,
        &s3c_device_usb_hsudc,
	&mango24_smsc911x,
	&mango24_device_gpiokeys,
	&mango24_leds_device,
        &mango24_lcd_lb070wv6,
};

static void __init smdk2416_map_io(void)
{
	s3c24xx_init_io(smdk2416_iodesc, ARRAY_SIZE(smdk2416_iodesc));
	s3c24xx_init_clocks(12000000);
	s3c24xx_init_uarts(smdk2416_uartcfgs, ARRAY_SIZE(smdk2416_uartcfgs));
}

static void mango24_board_gpio_setup(void)
{
        unsigned int gpio;
/* GPB3 TOUT3 LCD_BRIGHTNESS_CTL */
/* GPB4 TCLK CAM_PWRDN */
        for (gpio = S3C2410_GPB(3); gpio <= S3C2410_GPB(4); gpio++) {
                s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(1));
                s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
        }
/* GPF0 EINT0 KEY_DIN0 */
/* GPF1 EINT1 KEY_DIN1 */
        for (gpio = S3C2410_GPF(0); gpio <= S3C2410_GPF(1); gpio++) {
                s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(0));
                s3c_gpio_setpull(gpio, S3C_GPIO_PULL_UP);
        }
/* GPF2 EINT2 LED0 */
/* GPF3 EINT3 LED1 */
        for (gpio = S3C2410_GPF(2); gpio <= S3C2410_GPF(3); gpio++) {
                s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(1));
                s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
        }
/* GPG0 EINT8 WIFI_ENABLE */
        s3c_gpio_cfgpin(S3C2410_GPG(0), S3C_GPIO_SFN(1));
        s3c_gpio_setpull(S3C2410_GPG(0), S3C_GPIO_PULL_NONE);
/* GPG1 EINT9 WIFI_WKUPn */
        s3c_gpio_cfgpin(S3C2410_GPG(1), S3C_GPIO_SFN(1));
        s3c_gpio_setpull(S3C2410_GPG(1), S3C_GPIO_PULL_UP);
/* GPG2 EINT10 BT_WKUPn */
        s3c_gpio_cfgpin(S3C2410_GPG(2), S3C_GPIO_SFN(1));
        s3c_gpio_setpull(S3C2410_GPG(2), S3C_GPIO_PULL_UP);
/* GPG3 EINT11 SD1_CDn */
        s3c_gpio_cfgpin(S3C2410_GPG(3), S3C_GPIO_SFN(0));
        s3c_gpio_setpull(S3C2410_GPG(3), S3C_GPIO_PULL_UP);
/* GPG4 EINT12 LCD_PWEREN */
        s3c_gpio_cfgpin(S3C2410_GPG(4), S3C_GPIO_SFN(1));
        s3c_gpio_setpull(S3C2410_GPG(4), S3C_GPIO_PULL_NONE);
/* GPG5 EINT13 IRQ_LAN */
        s3c_gpio_cfgpin(S3C2410_GPG(5), S3C_GPIO_SFN(2));
        s3c_gpio_setpull(S3C2410_GPG(5), S3C_GPIO_PULL_NONE);
/* GPG6 EINT14 HP_DETECT */
        s3c_gpio_cfgpin(S3C2410_GPG(6), S3C_GPIO_SFN(2));
        s3c_gpio_setpull(S3C2410_GPG(6), S3C_GPIO_PULL_NONE);

/* GPG8 EINT16 PWRENABLE_USBH */
        s3c_gpio_cfgpin(S3C2410_GPG(8), S3C_GPIO_SFN(1));
        s3c_gpio_setpull(S3C2410_GPG(8), S3C_GPIO_PULL_NONE);
/* GPG9 EINT17 BT_EN */
        s3c_gpio_cfgpin(S3C2410_GPG(9), S3C_GPIO_SFN(1));
        s3c_gpio_setpull(S3C2410_GPG(9), S3C_GPIO_PULL_NONE);
/* GPG10 EINT18 VBUS_DETECT */
        s3c_gpio_cfgpin(S3C2410_GPG(10), S3C_GPIO_SFN(2));
        s3c_gpio_setpull(S3C2410_GPG(10), S3C_GPIO_PULL_NONE);
}

static void mango24_iis_gpio_setup(void)
{
        unsigned int gpio;
        for (gpio = S3C2410_GPE(0); gpio <= S3C2410_GPE(4); gpio++) {
                s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
                s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
        }
}

static void __init mango24_smsc9220_init(void)
{
        u32 cs5;
#if 1
        /* configure nCS5 width to 16 bits */
        __raw_writel(0x0, S3C2412_SMIDCYR(5));
        __raw_writel(14, S3C2412_SMBWSTRD(5));
        __raw_writel(14, S3C2412_SMBWSTWRR(5));
        __raw_writel(4, S3C2412_SMBWSTOENR(5));
        __raw_writel(4, S3C2412_SMBWSTWENR(5));

        cs5 = __raw_readl(S3C2412_SMBCR(5));
        cs5 |= (1<<2)|(1<<0);
        cs5 &= ~((3<<20)|(3<<12));
        cs5 &= ~(3<<4);
        cs5 |= (1<<4);
        __raw_writel(cs5, S3C2412_SMBCR(5));
#endif
}

static void wifi_bt_enable(void)
{
/* GPG0 EINT8 WIFI_ENABLE */
	gpio_request(S3C2410_GPG(0), "WIFI_ENABLE");
	gpio_direction_output(S3C2410_GPG(0), 1);
	gpio_free(S3C2410_GPG(0));
/* GPG1 EINT9 WIFI_WKUPn */
	gpio_request(S3C2410_GPG(1), "WIFI_WKUPn");
	gpio_direction_output(S3C2410_GPG(1), 1);
	mdelay(10);
	gpio_direction_output(S3C2410_GPG(1), 0);
	mdelay(10);
	gpio_direction_output(S3C2410_GPG(1), 1);
	mdelay(10);
	gpio_free(S3C2410_GPG(1));

/* GPG9 EINT17 BT_EN */
	gpio_request(S3C2410_GPG(9), "BT_ENABLE");
	gpio_direction_output(S3C2410_GPG(9), 1);
	gpio_free(S3C2410_GPG(9));

/* GPG2 EINT10 BT_WKUPn */
	gpio_request(S3C2410_GPG(2), "BT_WKUPn");
	gpio_direction_output(S3C2410_GPG(2), 1);
	mdelay(10);
	gpio_direction_output(S3C2410_GPG(2), 0);
	mdelay(10);
	gpio_direction_output(S3C2410_GPG(2), 1);
	mdelay(10);
	gpio_free(S3C2410_GPG(2));
}
	
static void __init smdk2416_machine_init(void)
{
	mango24_board_gpio_setup();

	s3c_i2c0_set_platdata(NULL);
        i2c_register_board_info(0, mango24_i2c0_board_info,
                                ARRAY_SIZE(mango24_i2c0_board_info));

        s3c24xx_ts_set_platdata(&s3c_ts_platform);

	s3c_sdhci0_set_platdata(&smdk2416_hsmmc0_pdata);
	s3c_sdhci1_set_platdata(&smdk2416_hsmmc1_pdata);

	mango24_smsc9220_init();
	// mango24_iis_gpio_setup();

        s3c24xx_hsudc_set_platdata(&smdk2416_hsudc_platdata);

#if 1
	gpio_request(S3C2410_GPB(3), "Display Backlight");
	gpio_direction_output(S3C2410_GPB(3), 1);
	gpio_free(S3C2410_GPB(3));

	gpio_request(S3C2410_GPG(4), "Display Power");
	gpio_direction_output(S3C2410_GPG(4), 1);
	gpio_free(S3C2410_GPG(4));

	gpio_request(S3C2410_GPG(8), "USBH_PWREN");
	gpio_direction_output(S3C2410_GPG(8), 1);
	gpio_free(S3C2410_GPG(8));
#endif
	wifi_bt_enable();

        s3c_fb_set_platdata(&smdk2416_fb_platdata);

        mango24_lb070wv6_set_power(&mango24_lcd_lb070wv6_data, 1);

        s3c_nand_set_platdata(&smdk_nand_info);

	platform_add_devices(smdk2416_devices, ARRAY_SIZE(smdk2416_devices));

        s3c_pm_init();
}

MACHINE_START(SMDK2416, "SMDK2416")
	/* Maintainer: Yauhen Kharuzhy <jekhor@gmail.com> */
	.boot_params	= S3C2410_SDRAM_PA + 0x100,

	.init_irq	= s3c24xx_init_irq,
	.map_io		= smdk2416_map_io,
	.init_machine	= smdk2416_machine_init,
	.timer		= &s3c24xx_timer,
MACHINE_END
