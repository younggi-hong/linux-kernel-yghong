
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/sched.h>
#include <linux/interrupt.h>
#include <linux/slab.h>				/* kmalloc */

#include <asm/uaccess.h>			/* copy_to_user */

#include <asm/io.h>
#include <asm/mach/irq.h>

#include <asm/irq.h>
#include <mach/hardware.h>

#include <mach/regs-gpio.h>
#include <mach/regs-irq.h>				/* Regs-irq.h (arch\arm\mach-s3c2410\include\mach) */
#include <mach/wave_reg.h>			/* Wave_reg.h (arch\arm\plat-s3c24xx\include\mach) */

#define WAVE_INT_DEV_NAME			"waveint"
#define WAVE_INT_DEV_MAJOR		240

#define WAVE_RX_TX_BUF_UPDATE		1

#if 1	/* SHKO_TEST */
RX_FRAME_DATA wave_rx_data_frame[WAVE_RX_QUEUE_NUM];
int wave_rx_data_frame_write_count = 0;
int wave_rx_data_frame_read_count = 0;
#endif



 
static irqreturn_t wave_rx_int(int irq, void *dev_id, struct pt_regs *regs)
{
	volatile unsigned int status, val;
	volatile unsigned int len, len_org;
	volatile unsigned int rx_info;
	unsigned char rssi;
	unsigned char data_rate;
	volatile unsigned int rx_data;
	int i, j;

	//val = __raw_readl(S3C2510_IOPEXTINTPND);
	//val = __raw_readl(S3C2510_IOPDATA1);
	//printk("[wave_rx_int] val1=0x%08x\n", val);

	/* EXT4 인터럽트만 Disable */
  #if 0	//SHKO, Origin
	__raw_writel(S3C2510_EXTMASK, 0x0000003F);
  #endif

  #if 0	//SHKO, Origin
	status = __raw_readl(WAVE_MAC_INT_STATUS_REG);		/* Interrupt Clear */
  #endif
  
	//printk("[wave_rx_int] status=0x%08x\n", status);
	if ( status & SCH_AC1_TX_COMPLETE_INT)
     	{
     		printk("[wave_rx_int] SCH_AC1_TX_COMPLETE_INT!!\n");
     	}
     	if ( status & SCH_AC2_TX_COMPLETE_INT)
     	{
     		printk("[wave_rx_int] SCH_AC2_TX_COMPLETE_INT!!\n");
     	}
     	if ( status & SCH_AC3_TX_COMPLETE_INT)
     	{
     		printk("[wave_rx_int] SCH_AC3_TX_COMPLETE_INT!!\n");
     	}
     	if ( status & SCH_AC4_TX_COMPLETE_INT)
     	{
     		printk("[wave_rx_int] SCH_AC4_TX_COMPLETE_INT!!\n");
     	}
     	if ( status & SCH_AC1_RETX_LIMIT_OVERFLOW_INT)
     	{
     		printk("[wave_rx_int] SCH_AC1_RETX_LIMIT_OVERFLOW_INT!!\n");
     	}
     	if ( status & SCH_AC2_RETX_LIMIT_OVERFLOW_INT)
     	{
     		printk("[wave_rx_int] SCH_AC2_RETX_LIMIT_OVERFLOW_INT!!\n");
     	}
     	if ( status & SCH_AC3_RETX_LIMIT_OVERFLOW_INT)
     	{
     		printk("[wave_rx_int] SCH_AC3_RETX_LIMIT_OVERFLOW_INT!!\n");
     	}
     	if ( status & SCH_AC4_RETX_LIMIT_OVERFLOW_INT)
     	{
     		printk("[wave_rx_int] SCH_AC4_RETX_LIMIT_OVERFLOW_INT!!\n");
     	}
     	if ( status & CCH_AC1_TX_COMPLETE_INT)
     	{
     		printk("[wave_rx_int] CCH_AC1_TX_COMPLETE_INT!!\n");
     	}
     	if ( status & CCH_AC2_TX_COMPLETE_INT)
     	{
     		printk("[wave_rx_int] CCH_AC2_TX_COMPLETE_INT!!\n");
     	}
     	if ( status & CCH_AC3_TX_COMPLETE_INT)
     	{
     		printk("[wave_rx_int] CCH_AC3_TX_COMPLETE_INT!!\n");
     	}
     	if ( status & CCH_AC4_TX_COMPLETE_INT)
     	{
     		//printk("[wave_rx_int] CCH_AC4_TX_COMPLETE_INT!!\n");
     	}
     	if ( status & CCH_AC1_RETX_LIMIT_OVERFLOW_INT)
     	{
     		printk("[wave_rx_int] CCH_AC1_RETX_LIMIT_OVERFLOW_INT!!\n");
     	}
     	if ( status & CCH_AC2_RETX_LIMIT_OVERFLOW_INT)
     	{
     		printk("[wave_rx_int] CCH_AC2_RETX_LIMIT_OVERFLOW_INT!!\n");
     	}
     	if ( status & CCH_AC3_RETX_LIMIT_OVERFLOW_INT)
     	{
     		printk("[wave_rx_int] CCH_AC3_RETX_LIMIT_OVERFLOW_INT!!\n");
     	}
     	if ( status & CCH_AC4_RETX_LIMIT_OVERFLOW_INT)
     	{
     		printk("[wave_rx_int] CCH_AC4_RETX_LIMIT_OVERFLOW_INT!!\n");
     	}
     	if ( status & RX_DATA_FRAME_INT)
     	{
	  #if 0	//SHKO, Origin
		rx_info = __raw_readl(WAVE_MAC_RX_INFO_QUEUE_FOR_DATA_FRAME_REG);
	  #endif
				
     		len_org = rx_info & 0xFFF;
     		rssi = (rx_info >> 16) & 0xFF;
     		data_rate = (rx_info >> 12) & 0xF;

     		wave_rx_data_frame[wave_rx_data_frame_write_count].rssi = (unsigned int)rssi;
     		wave_rx_data_frame[wave_rx_data_frame_write_count].data_rate= (unsigned int)data_rate;
     		wave_rx_data_frame[wave_rx_data_frame_write_count].len= (unsigned int)len_org;

		i = 0;
     		wave_rx_data_frame[wave_rx_data_frame_write_count].buf[i++] = (unsigned int)rssi;
     		wave_rx_data_frame[wave_rx_data_frame_write_count].buf[i++] = (unsigned int)data_rate;

     		if ( (len_org%4) == 0)
     		{
     			len = len_org/4;
     			for ( j = 0; j < len; j++)
     			{
     			#if WAVE_RX_TX_BUF_UPDATE
     				wave_rx_data_frame[wave_rx_data_frame_write_count].buf[i] = __raw_readl(WAVE_MAC_RX_DATA_QUEUE_DATA_FRAME_REG);
     			#else
     				rx_data = __raw_readl(WAVE_MAC_RX_DATA_QUEUE_DATA_FRAME_REG);
     				wave_rx_data_frame[wave_rx_data_frame_write_count].buf[i] = ENDIAN_SWAP32(rx_data);
     			#endif
     			
     				i++;
     			}
     		}
     		else
     		{
     			len = (len_org/4) + 1;
     			for ( j = 0; j < len; j++)
     			{
     			#if WAVE_RX_TX_BUF_UPDATE
     				wave_rx_data_frame[wave_rx_data_frame_write_count].buf[i] = __raw_readl(WAVE_MAC_RX_DATA_QUEUE_DATA_FRAME_REG);
     			#else
     				rx_data = __raw_readl(WAVE_MAC_RX_DATA_QUEUE_DATA_FRAME_REG);
     				wave_rx_data_frame[wave_rx_data_frame_write_count].buf[i] = ENDIAN_SWAP32(rx_data);
     			#endif

     				i++;
     			}
     		}

     		wave_rx_data_frame_write_count++;
     		if (wave_rx_data_frame_write_count == WAVE_RX_QUEUE_NUM)
     			wave_rx_data_frame_write_count = 0;
     		
     	}
     	if ( status & RX_MANAGEMENT_FRAME_INT)
     	{
     		printk("[wave_rx_int] RX_MANAGEMENT_FRAME_INT!!\n");
     	}
     	if ( status & DATA_QUEUE_OVERFLOW_INT)
     	{
     		rx_info = __raw_readl(WAVE_MAC_RX_INFO_QUEUE_FOR_DATA_FRAME_REG);
				
     		len_org = rx_info & 0xFFF;
     		
     		if ( (len_org%4) == 0)
     		{
     			len = len_org/4;
     			for ( j = 0; j < len; j++)
     			{
     				rx_data = __raw_readl(WAVE_MAC_RX_DATA_QUEUE_DATA_FRAME_REG);
     			}
     		}
     		else
     		{
     			len = (len_org/4) + 1;
     			for ( j = 0; j < len; j++)
     			{
     				rx_data = __raw_readl(WAVE_MAC_RX_DATA_QUEUE_DATA_FRAME_REG);
     				
     			}
     		}
     		printk("[wave_rx_int] Data Queue Overflow Interrupt!!\n");
     	}
     	if ( status & MANAGEMENT_QUEUE_OVERFLOW_INT)
     	{
     		printk("[wave_rx_int] Management Queue Overflow Interrupt!!\n");
     	}
     	if ( status & DATA_QUEUE_OVERFLOW_CLEAR_INT)
     	{
     		printk("[wave_rx_int] Data Queue Overflow Clear Interrupt!!\n");
     	}
     	if ( status & MANAGEMENT_QUEUE_OVERFLOW_CLEAR_INT)
     	{
     		printk("[wave_rx_int] Management Queue Overflow Clear Interrupt!!\n");
     	}
     	if ( status & TX_START_OF_EXTRA_QUEUE_INT)
     	{
     		printk("[wave_rx_int] TX_START_OF_EXTRA_QUEUE_INT!!\n");
     	}
	
     	

     	/* EXT4 인터럽트만 Enable */
    #if 0	//SHKO, Origin
	__raw_writel(S3C2510_EXTMASK, 0x0000002F);
  #endif

	return IRQ_HANDLED;
}
 
static ssize_t wave_read(struct file *filp, char *buf,size_t count, loff_t *l)
{
	 RX_DATA_FRAME_INFO *ptrRxInfo;
	 unsigned int len = 0;
	 
       // int tmp;
        //tmp = key_data;
        //interruptible_sleep_on(&key_queue);
        //copy_to_user(buf, &key_data, sizeof(tmp));
       
	//printk("[wave_read] [%d][%d]\n", wave_rx_data_frame_write_count, wave_rx_data_frame_read_count);
	
        if (wave_rx_data_frame_write_count != wave_rx_data_frame_read_count)
        {
        	if (wave_rx_data_frame[wave_rx_data_frame_read_count].len >= count)
        	{
        		printk("[wave_read] rx len is very large=%d\n", wave_rx_data_frame[wave_rx_data_frame_read_count].len);
        		return(0);
        	}
        	//ptrRxInfo = (RX_DATA_FRAME_INFO *) filp->private_data;
        	//ptrRxInfo->rssi = wave_rx_data_frame[wave_rx_data_frame_read_count].rssi;
        	//ptrRxInfo->data_rate = wave_rx_data_frame[wave_rx_data_frame_read_count].data_rate;
        	copy_to_user(buf, wave_rx_data_frame[wave_rx_data_frame_read_count].buf, wave_rx_data_frame[wave_rx_data_frame_read_count].len);

        	len = wave_rx_data_frame[wave_rx_data_frame_read_count].len;

        	wave_rx_data_frame_read_count++;
     		if (wave_rx_data_frame_read_count == WAVE_RX_QUEUE_NUM)
     			wave_rx_data_frame_read_count = 0;

     		//printk("[wave_read] len=%d\n", len);
        	return((ssize_t)len);
        }
        
        return 0;
}
 
static int wave_open(struct inode *inode,struct file *filp)
{
	int rc;
	//RX_DATA_FRAME_INFO *ptrRxInfo;

	//ptrRxInfo = kmalloc(sizeof(RX_DATA_FRAME_INFO), GFP_KERNEL);
	//filp->private_data = ptrRxInfo;
	
        printk("waveint Device Open, S3C2410_GPG(7) = %d\n", S3C2410_GPG(7));

#if 1	/* SHKO_TEST */
        wave_rx_data_frame_write_count = 0;
        wave_rx_data_frame_read_count = 0;
#endif

        if ((rc = request_irq(S3C2410_GPG(7), wave_rx_int, IRQF_DISABLED, WAVE_INT_DEV_NAME, NULL)))
        {
        	printk( KERN_WARNING "%s: unable to get IRQ %d (irqval=%d).\n",
			"waveint", S3C2410_GPG(7), rc);

		free_irq( S3C2410_GPG(7), NULL);	// free the one we got
		return ( -EAGAIN);
        }

#if 0
        retval = request_irq(dev->irq, smsc911x_irqhandler,
			     irq_flags | IRQF_SHARED, dev->name, dev);
	if (retval) {
		SMSC_WARNING(PROBE,
			"Unable to claim requested irq: %d", dev->irq);
		goto out_unmap_io_3;
	}
#endif

        return 0;
}
 
static int wave_release(struct inode *inode, struct file *filp)
{
	printk("waveint Device Released \n");
  #if 0	//SHKO, Origin
	free_irq( S3C2510_INTOFFSET_EXT4, NULL);	// free the one we got
  #endif
	return 0;
}
 
static struct file_operations waveint_fops = {
        .open= wave_open,
        .read= wave_read,
        .release= wave_release,
};
 
static int __init waveint_init(void)
{
        int res, result;

        printk("[waveint_init] Start!!\n");
 
        if((result = register_chrdev(WAVE_INT_DEV_MAJOR,WAVE_INT_DEV_NAME, &waveint_fops)) < 0)
        {
                printk(" register_chrdev() FAIL ! \n");
                return result;
        }
 
        return 0;
}
 
void __exit waveint_exit(void)
{
        //disable_irq(KEY_IRQ);
        //free_irq(KEY_IRQ, NULL);
        unregister_chrdev(WAVE_INT_DEV_MAJOR,WAVE_INT_DEV_NAME);
}
 
module_init(waveint_init);
module_exit(waveint_exit);



