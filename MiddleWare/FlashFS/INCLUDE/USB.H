/***

	*************************************************************************
	*																		*
	*		header file for USB module										*
	*																		*
	*														USB.H			*
	*************************************************************************
	ALL RIGHTS RESERVED, COPYRIGHT(C) FUJITSU FRONTECH LIMITED. 2002-2007

	SN			Date		Name		Revision.No.	Contents
	-------------------------------------------------------------------------
	001-ZZ01	2002/10/28	M.Banba		<BRZ-001>		The First Version
	002-ZZ03	2003/04/17	A.Maruyama	<BRZ-006>		Delete definition of port for TEST-PCB
														Change base-address for Real-PCB
	003-ZZ05	2003/07/05	A.Maruyama	<BRZ-202>		add function prottype for change ipl<-->main interface
														:UsbSetStatusFromBoot()
	004-AA52	2007/11/02	A.Maruyama	<BRZ-1554>		for Dual BRU
														-The definition of PID was moved from USB_DATA.c and change name
														 :USB_PID
														-add definition of 2nd.-PID
														 :USB_PID2
														-add Variable
														 :device_descriptor_basis
														-add function
														 :UsbMakeDeviceDescriptor()

COMMENT END
***/
/*----------------------------------------------------------------------*/
/*	USB割り込み処理														*/
/*----------------------------------------------------------------------*/
/*	機能:	BV割り込み処理(受信)										*/
/*																		*/
/*	引数:	なし														*/
/*																		*/
/*	復帰:	なし														*/
/*																		*/
/*----------------------------------------------------------------------*/
extern	UCHAR	chk_remote_wakeup;
void	UsbIrq( void );

/*------------------------------------------------------*/
/*	definition of Product-ID							*/
/*	Rev.(AA52:BRZ-1154)		for Dual BRU				*/
/*	 - The definition of PID was moved from USB_DATA.c	*/
/*	 - Label change PID -> USB_PID						*/
/*------------------------------------------------------*/
#define	USB_PID		0x1082		/* 												*/
#define	USB_PID2	0x118E		/* 2nd Product ID				(AA52:BRZ-1554)	*/

/*------------------------------------------------------*/
/*	Endpoint serial number definitions					*/
/*------------------------------------------------------*/
#define	EP0						0			/* Endpoint 0 汎用 */
#define	EP0RX					0			/* Endpoint 0 受信用 */
#define	EP1						1			/* Endpoint 1 */
#define	EP2						2			/* Endpoint 2 */
#define	EP3						3			/* Endpoint 3 */
#define	EP0TX					4			/* Endpoint 0 送信用 */
#define	EP_MAX					4			/* エンドポイント最大数 */
/*****************************************************************************
    Standard Request Codes  ( bRequest )    
*******************************************/
#define	GET_STATUS				 0
#define	CLEAR_FEATURE			 1
#define	SET_FEATURE				 3
#define	SET_ADDRESS				 5
#define	GET_DESCRIPTOR			 6
#define	SET_DESCRIPTOR			 7
#define	GET_CONFIGURATION		 8
#define	SET_CONFIGURATION		 9
#define	GET_INTERFACE			10
#define	SET_INTERFACE			11
#define	SYNCH_FRAME				12

/*****************************************************************************
    Descriptor Types    
***********************/
#define	DEVICE					1
#define	CONFIGURATION			2
#define	STRING					3
#define	INTERFACE				4
#define	ENDPOINT				5

/*****************************************************************************
    Feature Selector    
***********************/
#define	DEVICE_REMOTE_WAKEUP	1
#define	ENDPOINT_STALL			0

/*****************************************************************************
    Transfer Types    
***********************/
#define	CONTROL					0				/* bit 0-1 : 00 */
#define	ISOCHRONOUS				1				/* bit 0-1 : 01 */
#define	BULK					2				/* bit 0-1 : 10 */
#define	INTERRUPT				3				/* bit 0-1 : 11 */

#define	M_EP_NUM				0x0F

/* Device Requests */
typedef	UCHAR	bmRequestType;
typedef	UCHAR	bRequest;
typedef	USHORT	wValue;
typedef	USHORT	wIndex;
typedef	USHORT	wLength;

/* Descriptor's common */
typedef	UCHAR	bLength;
typedef	UCHAR	bDescriptorType;

/* Device Descriptor */
typedef	USHORT	bcdUSB;
typedef	UCHAR	bDeviceClass;
typedef	UCHAR	bDeviceSubClass;
typedef	UCHAR	bDeviceProtocol;
typedef	UCHAR	bMaxPacketSize0;
typedef	USHORT	idVendor;
typedef	USHORT	idProduct;
typedef	USHORT	bcdDevice;
typedef	UCHAR	iManufacturer;
typedef	UCHAR	iProduct;
typedef	UCHAR	iSerialNumber;
typedef	UCHAR	bNumConfigurations;

/* Configuration Descriptor */
typedef	USHORT	wTotalLength;
typedef	UCHAR	bNumInterfaces;
typedef	UCHAR	bConfigurationValue;
typedef	UCHAR	iConfiguration;
typedef	UCHAR	bmAttributes;
typedef	UCHAR	MaxPower;

/* Interface Descriptor */
typedef	UCHAR	bInterfaceNumber;
typedef	UCHAR	bAlternateSetting;
typedef	UCHAR	bNumEndpoints;
typedef	UCHAR	bInterfaceClass;
typedef	UCHAR	bInterfaceSubClass;
typedef	UCHAR	bInterfaceProtocol;
typedef	UCHAR	iInterface;

/* Endpoint Descriptor */
typedef	UCHAR	bEndpointAddress;
/* typedef	UCHAR	bmAttributes; *//* defined at Config.. */
typedef	USHORT	wMaxPacketSize;
typedef	UCHAR	bInterval;

/* String Descriptor */


/*****************************************************************************
    USB Device Requests     
***************************/
typedef struct Device_Request {
	bmRequestType			bmRequestType;		/*  */
	bRequest				bRequest;			/*  */
	wValue					wValue;				/*  */
	wIndex					wIndex;				/*  */
	wLength					wLength;			/*  */
} Device_Request;

/* bmRequestType D7     Data xfer direction */
#define	REQUEST_XFER		0x80
#define	HOST_to_DEVICE		0x00
#define	DEVICE_to_HOST		0x80

/* bmRequestType D6..5  Type */
#define	REQUEST_TYPE		0x60
#define	STANDARD_TYPE		0x00
#define	CLASS_TYPE			0x20
#define	VENDOR_TYPE			0x40

/* bmRequestType D4..0  Recipient */
#define	REQUEST_RECIPIENT	0x1F
#define	DEVICE_RECIPIENT	0x00
#define	INTERFACE_RECICPENT	0x01
#define	ENDPOINT_RECICPENT	0x02

/*****************************************************************************
    Standard USB Descriptor Definitions    
******************************************/
typedef const struct String_Descriptor {
	bLength				bLength;
	bDescriptorType		bDescriptorType;
/*	USHORT			string[];	*/
} String_Desc;

typedef const struct Endpoint_Descriptor {
	bLength				bLength;
	bDescriptorType		bDescriptorType;
	bEndpointAddress	bEndpointAddress;
	bmAttributes		bmAttributes;
	wMaxPacketSize		wMaxPacketSize;
	bInterval			bInterval;
} Endpoint_Desc;

typedef const struct Interface_Descriptor {
	bLength				bLength;
	bDescriptorType		bDescriptorType;
	bInterfaceNumber	bInterfaceNumber;
	bAlternateSetting	bAlternateSetting;
	bNumEndpoints		bNumEndpoints;
	bInterfaceClass		bInterfaceClass;
	bInterfaceSubClass	bInterfaceSubClass;
	bInterfaceProtocol	bInterfaceProtocol;
	iInterface			iInterface;
	Endpoint_Desc		*p_EP_desc;
						/* Endpoint Descriptorを指すポインタ */
} Interface_Desc;

/*
 * 同じbInterfaceNumberで違うbAlternateSettingをもつ Descriptorが
 * 設定できるため Configuration と Interface をこの構造体で仲介する
 */
typedef struct Configuration_Interface {
	bInterfaceNumber	bInterfaceNumber;		/* p_IF_descが指すDescriptorのbInterfaceNumber */
	bAlternateSetting	bAlternateSetting;		/* p_IF_descが指すDescriptorがもつAlternateSetting数 */
	bAlternateSetting	currentAlternateSetting;/* 現在設定されているAlternateSetting */
	Interface_Desc		*p_IF_desc;
						/* Interface Descriptorを指すポインタ */
} Config_if;

typedef const struct Configuration_Descriptor {
	bLength				bLength;
	bDescriptorType		bDescriptorType;
	wTotalLength		wTotalLength;
	bNumInterfaces		bNumInterfaces;
	bConfigurationValue	bConfigurationValue;
	iConfiguration		iConfiguration;
	bmAttributes		bmAttributes;
	MaxPower			MaxPower;
	Config_if			*p_CFG_if;
						/* 仲介用構造体を指すポインタ */
} Config_Desc;

	/*------------------------------------------------------*/
	/*	Rev.(AA52:BRZ-1554)	for Dual BRU					*/
	/*	 delete 'const'										*/
	/*------------------------------------------------------*/
typedef /*const*/ struct Device_Descriptor {
	bLength				bLength;
	bDescriptorType		bDescriptorType;
	bcdUSB				bcdUSB;
	bDeviceClass		bDeviceClass;
	bDeviceSubClass		bDeviceSubClass;
	bDeviceProtocol		bDeviceProtocol;
	bMaxPacketSize0		bMaxPacketSize0;
	idVendor			idVendor;
	idProduct			idProduct;
	bcdDevice			bcdDevice;
	iManufacturer		iManufacturer;
	iProduct			iProduct;
	iSerialNumber		iSerialNumber;
	bNumConfigurations	bNumConfigurations;
	Config_Desc			*p_CFG_desc;
						/* Configuration Descriptorを指すポインタ */
} Device_Desc;

/*------------------------------------------------------*/
/*	Endpoint 制御用構造体								*/
/*------------------------------------------------------*/
typedef const struct EP_List_C {
	UCHAR	*recv_byte_cnt;			/* 受信バイトカウントレジスタ */
	UCHAR	*control_R;				/* 制御レジスタ(Read) */
	USHORT	*control_W;				/* 制御レジスタ(Write) */
	UCHAR	*datatgl_R;				/* データトグルレジスタ(Read) */
	USHORT	*datatgl_W;				/* データトグルレジスタ(Write) */
	UCHAR	*payload_R;				/* ペイロードレジスタ(Read) */
	USHORT	*payload_W;				/* ペイロードレジスタ(Write) */
	UCHAR	*fifo_R;				/* 受信FIFOアドレス */
	UCHAR	*fifo_W;				/* 送信FIFOアドレス */
	UCHAR	b_recv_pktrdy;			/* 受信パケットレディ セット/リセット ビット*/
	UCHAR	b_trns_pktrdy;			/* 送信パケットレディ セット/リセット ビット*/
	UCHAR	b_pktrdy_int;			/* パケットレディ割込み ビット */
	UCHAR	b_stall;				/* ストール ビット */
	UCHAR	b_clrFIFO;				/* 送信FIFOクリア ビット */
} EP_LIST_C;

typedef struct EP_List_V {
	uint	total_cnt;				/* 送受信データ総数 */
	uint	byte_cnt;				/* 送受信データ数 */
	UCHAR	*buf;					/* データ用バッファ */
	void	(*callback)(UCHAR *buf, uint size);	/* CallBack関数 */
} EP_LIST_V;

/* 5.   USB Device Status
*/
typedef struct USB_Status {
    Config_Desc *configuration;
    void        (*callback)(void);  /* CallBack function */
    UCHAR       remote_wakeup;
    UCHAR       address;
    UCHAR       dvcstate;           /* Current device state */      /* S990712 */
    UCHAR       stall_req;          /* STALL request information */
} USB_STATUS;
    #define REQ_STALL   0x80            /* STALL request bit */
    #define DEFAULT_STATE   0
    #define ADDRESS_STATE   1
    #define CONFIGURED_STATE    2
/*------------------------------------------------------*/
/*  Register Address Assignment Control					*/
/*  (ZZZ-001)											*/
/*	Rev.(ZZ03:BRZ-006)									*/
/*	 change base-address for Real-PCB					*/
/*------------------------------------------------------*/
#define		REG_BASE_ADDR	0x00300000

#define		REG_R(addr)		(volatile char *)( ((addr | 0xC0)*2 ) | REG_BASE_ADDR )

#define		REG_W(addr)		(volatile short *)( ((addr | 0x40)*2 ) | REG_BASE_ADDR )

#define		FIFO_R(addr)	(volatile char *)( ((addr | 0x40)*2 ) | REG_BASE_ADDR )

#define		FIFO_W(addr)	(volatile short *)( ((addr | 0xC0)*2 ) | REG_BASE_ADDR )
/*------------------------------------------------------*/
/*    Register Offset Address Definitions				*/
/*------------------------------------------------------*/
	/*----------------------------------------------*/
	/* Rx fifos 									*/
	/*----------------------------------------------*/
#define EP0RXFIFO               0x00        /* EP0 receive FIFO data */
#define EP1RXFIFO               0x01        /* EP1 receive FIFO data */
#define EP2RXFIFO               0x02        /* EP2 receive FIFO data */
	/*----------------------------------------------*/
	/* Tx fifos 									*/
	/*----------------------------------------------*/
#define EP0TXFIFO               0x00        /* EP0 transmit FIFO data */
#define EP1TXFIFO               0x01        /* EP1 transmit FIFO data */
#define EP2TXFIFO               0x02        /* EP2 transmit FIFO data */
#define EP3TXFIFO               0x03        /* EP3 transmit FIFO data */
	/*----------------------------------------------*/
	/* Common control and status registers 			*/
	/*----------------------------------------------*/
#define DVCADR                  0x00		/* Device Address Register					*/
#define DVCSTAT                 0x01		/* Device State Register					*/
#define 	B_DEFAULT_STATE         0x01		/* Default state - user bit				*/
#define 	B_ADDRESS_STATE         0x02		/* Address state - user bit				*/
#define 	B_CONFIG_STATE          0x04		/* Configuration state - user bit		*/
#define 	B_SUSPENDED_STATE       0x08		/* Suspended state - Hardware Indicates */
#define 	B_REMOTE_WAKEUP         0x10		/* Remote wakeup - Software invoke		*/
#define 	B_BUS_RESET_CLR         0x20		/* USB bus reset status clear			*/
#define PKTERR                  0x02		/* Packet Error Register					*/
#define 	B_BIT_STUFF_ERR         0x01		/* Bit stuff error						*/
#define 	B_DATA_CRC_ERR          0x02		/* Data CRC error						*/
#define 	B_ADDR_CRC_ERR          0x04		/* Address CRC error					*/
#define 	B_PID_ERR               0x08		/* PID error							*/
#define FIFOSTAT1               0x03		/* FIFO Status Register 1					*/
#define 	B_RXFIFO_0_FULL         0x01		/* Receive FIFO 0 full					*/
#define 	B_RXFIFO_0_EMPTY        0x02		/* Receive FIFO 0 empty					*/
#define 	B_FIFO_1_FULL           0x04		/* FIFO 1 full							*/
#define 	B_FIFO_1_EMPTY          0x08		/* FIFO 1 empty							*/
#define FIFOSTAT2               0x04		/* FIFO Status Register 2					*/
#define 	B_TXFIFO_0_FULL         0x01		/* Send FIFO 0 full						*/
#define 	B_TXFIFO_0_EMPTY        0x02		/* Send FIFO 0 empty					*/
#define 	B_FIFO_2_FULL           0x04		/* FIFO 2 full							*/
#define 	B_FIFO_2_EMPTY          0x08		/* FIFO 2 empty							*/
#define 	B_FIFO_3_FULL           0x10		/* FIFO 3 full							*/
#define 	B_FIFO_3_EMPTY          0x20		/* FIFO 3 empty							*/
#define PKTRDY                  0x08		/* Endpoint Packet Ready Register			*/
#define		B_EP0RXPKTRDY           0x01		/* EP0 receive packet ready				*/
#define		B_EP1RXPKTRDY           0x02		/* EP1 receive packet ready				*/
#define		B_EP2RXPKTRDY           0x04		/* EP2 receive packet ready				*/
#define		B_EP0TXPKTRDY           0x10		/* EP0 transmit packet ready			*/
#define		B_EP1TXPKTRDY           0x20		/* EP1 transmit packet ready			*/
#define		B_EP2TXPKTRDY           0x40		/* EP2 transmit packet ready			*/
#define		B_EP3TXPKTRDY           0x80		/* EP3 transmit packet ready			*/
#define EP0RXCNT                0x09		/* Endpoint 0 Receive Byte Count Register	*/
#define EP1RXCNT                0x0A		/* Endpoint 1 Receive Byte Count Register	*/
#define EP2RXCNT                0x0B		/* Endpoint 2 Receive Byte Count Register	*/
#define CLRFIFO                 0x0E		/* Transmit FIFO clear						*/
#define		B_EP1_CLRFIFO           0x02		/* EP1 FIFO clear						*/
#define		B_EP2_CLRFIFO           0x04		/* EP2 FIFO clear						*/
#define		B_EP3_CLRFIFO           0x08		/* EP3 FIFO clear						*/
#define SYSCON                  0x0F		/* System Control Register					*/
#define		F_CMD                   0xA0		/* Oscillation stop command				*/
#define		B_SOFT_RESET            0x01		/* Soft reset bit						*/
	/*----------------------------------------------*/
	/*	8-byes setup registers						*/
	/*----------------------------------------------*/
#define REQUEST_REG  			0x10		/* 8-bytes setup command registers			*/
#define bmREQUESTTYPE			0x10		/* bmRequestType Setup Register				*/
#define bREQUEST     			0x11		/* bRequest Setup Register					*/
#define wVALUE_LSB   			0x12		/* wValue LSB Setup Register				*/
#define wVALUE_MSB   			0x13		/* wValue MSB Setup Register				*/
#define wINDEX_LSB   			0x14		/* wIndex LSB Setup Register				*/
#define wINDEX_MSB   			0x15		/* wIndex MSB Setup Register				*/
#define wLENGTH_LSB  			0x16		/* wLength LSB Setup Register				*/
#define wLENGTH_MSB  			0x17		/* wLength LSB Setup Register				*/
	/*----------------------------------------------*/
	/*	Pin function control 						*/
	/*----------------------------------------------*/
#define POLSEL                  0x1A		/* Polarity Selection Register				*/
#define		B_INTR					0x01		/* INTR polarity						*/
#define		B_DREQ					0x02		/* DREQ polarity						*/
#define		B_DACK					0x04		/* DACK polarity						*/
	/*----------------------------------------------*/
	/*	Interrupt enable control and status 		*/
	/*----------------------------------------------*/
#define INTENBL                 0x1B		/* Interrupt Enable Register				*/
#define INTSTAT                 0x1C		/* Interrupt Status Register				*/
#define		B_SETUP_RDY_INT         0x01		/* Setup ready interrupt				*/
#define		B_EP1PKTRDY_INT         0x02		/* EP1 packet ready interrupt			*/
#define		B_EP2PKTRDY_INT         0x04		/* EP2 packet ready interuppt			*/
#define		B_EP0RXPKTRDY_INT       0x08		/* EP0 receive packet ready interrupt	*/
#define		B_EP0TXPKTRDY_INT       0x10		/* EP0 transmit packet ready interrupt	*/
#define		B_BUS_RESET_INT         0x20		/* USB bus reset interrupt				*/
#define		B_SUSPENDED_STATE_INT   0x40		/* Suspended state interrupt			*/
#define		B_EP3PKTRDY_INT         0x80		/* EP3 packet ready interrupt			*/
	/*----------------------------------------------*/
	/*	DMA settings 								*/
	/*----------------------------------------------*/
#define DMACON                  0x1D		/* DMA Control Register						*/
#define   B_DMA_ENABLE            0x01			/* DMA enable							*/
#define   B_ADDRESS_MODE          0x02			/* Address mode							*/
#define   B_BYTE_COUNT            0x04			/* Byte count							*/
#define   B_TRNS_SIZE             0x08			/* Transfer size						*/
#define   B_TRNS_MODE             0x10			/* Transfer mode						*/
#define DMAINTVL                0x1E		/* DMA Interval Register					*/
	/*----------------------------------------------*/
	/*	Endpoint controls							*/
	/*----------------------------------------------*/
#define CONFIG_BIT              0x01        /* Configuration bit */
#define DATA_SEQUENCE_BIT       0x01        /* Data sequence toggle-bit */
	/*----------------------------------------------*/
	/*	EP0 rx controls								*/
	/*----------------------------------------------*/
#define EP0RXCON                0x20        /* Endpoint 0 Receive Control Register		*/
#define		B_EP0_CONFIG			CONFIG_BIT	/* Configuration bit					*/
#define EP0RXTGL                0x21        /* Endpoint 0 Receive Data-Toggle Register	*/
#define		B_EP0_DATA_SEQUENCE		DATA_SEQUENCE_BIT
#define EP0RXPLD                0x22        /* Endpoint 0 Receive Payload Register		*/
	/*----------------------------------------------*/
	/*	EP1 tx/rx controls							*/
	/*----------------------------------------------*/
#define EP1CON                  0x24        /* Endpoint 1 Control Register				*/
#define		B_EP1_CONFIG			CONFIG_BIT  /* Configuration bit					*/
#define		B_EP1_STALL			0x02        /* Stall bit								*/
#define EP1TGL                  0x25        /* Endpoint 1 Data-Toggle Register			*/
#define		B_EP1_DATA_SEQUENCE		DATA_SEQUENCE_BIT
#define EP1PLD                  0x26		/* Endpoint 1 Payload Register				*/
	/*----------------------------------------------*/
	/*	EP0 tx controls								*/
	/*----------------------------------------------*/
#define EP0TXCON                0x30		/* Endpoint 0 Send Control Register			*/
#define EP0TXTGL                0x31		/* Endpoint 0 Send Data-Toggle Register		*/
#define EP0TXPLD                0x32		/* Endpoint 0 Send Payload Register			*/
#define EP0STAT                 0x33		/* EP0 Status								*/
#define		B_EP0_SETUP_RDY         0x01		/* Setup ready							*/
#define		B_EP0_STALL             0x04		/* Stall								*/
#define		F_SETUP_STAGE           0x00		/* Setup stage							*/
#define		F_DATA_STAGE            0x08		/* Data Stage							*/
#define		F_STATUS_STAGE          0x10		/* Status stage							*/
	/*----------------------------------------------*/
	/*	EP2 tx/rx controls							*/
	/*----------------------------------------------*/
#define EP2CON                  0x34        /* Endpoint 2 Control Register				*/
#define		B_EP2_CONFIG			CONFIG_BIT  /* Configutration						*/
#define		B_EP2_STALL				0x02        /* Stall								*/
#define EP2TGL                  0x35        /* Endpoint 2 Data-Toggle Register			*/
#define		B_EP2_DATA_SEQUENCE		DATA_SEQUENCE_BIT
#define EP2PLD                  0x36        /* Endpoint 2 Payload Register				*/
	/*----------------------------------------------*/
	/*	EP3 tx controls 							*/
	/*----------------------------------------------*/
#define EP3CON                  0x38		/* Endpoint 3 Control Register				*/
#define		B_EP3_CONFIG			CONFIG_BIT  /* Configuration						*/
#define		B_EP3_STALL				0x02		/* Stall								*/
#define EP3TGL                  0x39		/* Endpoint 3 Data-Toggle Register			*/
#define		B_EP3_DATA_SEQUENCE		DATA_SEQUENCE_BIT
#define EP3PLD                  0x3A		/* Endpoint 3 Payload Register				*/
/*------------------------------------------------------*/
/* 	register definitions								*/
/*------------------------------------------------------*/
#define	ep0rxfifo			*(UCHAR*)FIFO_R(EP0RXFIFO)
#define	ep1rxfifo			*(UCHAR*)FIFO_R(EP1RXFIFO)
#define	ep2rxfifo			*(UCHAR*)FIFO_R(EP2RXFIFO)

#define	ep0txfifo			*(USHORT*)FIFO_W(EP0TXFIFO)
#define	ep1txfifo			*(USHORT*)FIFO_W(EP1TXFIFO)
#define	ep2txfifo			*(USHORT*)FIFO_W(EP2TXFIFO)
#define	ep3txfifo			*(USHORT*)FIFO_W(EP3TXFIFO)

#define	dvcadr_r			*(UCHAR*)REG_R(DVCADR)
#define	dvcadr_w			*(USHORT*)REG_W(DVCADR)
#define	dvcstat_r			*(UCHAR*)REG_R(DVCSTAT)
#define	dvcstat_w			*(USHORT*)REG_W(DVCSTAT)
#define	pkterr_r			*(UCHAR*)REG_R(PKTERR)
#define	fifostat1_r			*(UCHAR*)REG_R(FIFOSTAT1)
#define	fifostat2_r			*(UCHAR*)REG_R(FIFOSTAT2)

#define	pktrdy_r			*(UCHAR*)REG_R(PKTRDY)
#define	pktrdy_w			*(USHORT*)REG_W(PKTRDY)
#define	ep0rxcnt_r			*(UCHAR*)REG_R(EP0RXCNT)
#define	ep1rxcnt_r			*(UCHAR*)REG_R(EP1RXCNT)
#define	ep2rxcnt_r			*(UCHAR*)REG_R(EP2RXCNT)

#define	clrfifo_w			*(USHORT*)REG_W(CLRFIFO)

#define	syscon_w			*(USHORT*)REG_W(SYSCON)

#define	request_reg_r		*(UCHAR*)REG_R(REQUEST_REG)
#define	bmrequesttype_r		*(UCHAR*)REG_R(bmREQUESTTYPE)
#define	brequest_r			*(UCHAR*)REG_R(bREQUEST)
#define	wvalue_lsb_r		*(UCHAR*)REG_R(wVALUE_LSB)
#define	wvalue_msb_r		*(UCHAR*)REG_R(wVALUE_MSB)
#define	windex_lsb_r		*(UCHAR*)REG_R(wINDEX_LSB)
#define	windex_msb_r		*(UCHAR*)REG_R(wINDEX_MSB)
#define	wlength_lsb_r		*(UCHAR*)REG_R(wLENGTH_LSB)
#define	wlength_msb_r		*(UCHAR*)REG_R(wLENGTH_MSB)

#define	polsel_r			*(UCHAR*)REG_R(POLSEL)
#define	polsel_w			*(USHORT*)REG_W(POLSEL)
#define	intenbl_r			*(UCHAR*)REG_R(INTENBL)
#define	intenbl_w			*(USHORT*)REG_W(INTENBL)
#define	intstat_r			*(UCHAR*)REG_R(INTSTAT)
#define	dmacon_r			*(UCHAR*)REG_R(DMACON)
#define	dmacon_w			*(USHORT*)REG_W(DMACON)
#define	dmaintvl_r			*(UCHAR*)REG_R(DMAINTVL)
#define	dmaintvl_w			*(USHORT*)REG_W(DMAINTVL)

#define	ep0rxcon_r			*(UCHAR*)REG_R(EP0RXCON)
#define	ep0rxtgl_r			*(UCHAR*)REG_R(EP0RXTGL)
#define	ep0rxpld_r			*(UCHAR*)REG_R(EP0RXPLD)
#define	ep0rxpld_w			*(USHORT*)REG_W(EP0RXPLD)

#define	ep1con_r			*(UCHAR*)REG_R(EP1CON)
#define	ep1con_w			*(USHORT*)REG_W(EP1CON)
#define	ep1tgl_r			*(UCHAR*)REG_R(EP1TGL)
#define	ep1tgl_w			*(USHORT*)REG_W(EP1TGL)
#define	ep1pld_r			*(UCHAR*)REG_R(EP1PLD)
#define	ep1pld_w			*(USHORT*)REG_W(EP1PLD)

#define	ep0txcon_r			*(UCHAR*)REG_R(EP0TXCON)
#define	ep0txtgl_r			*(UCHAR*)REG_R(EP0TXTGL)
#define	ep0txpld_r			*(UCHAR*)REG_R(EP0TXPLD)
#define	ep0txpld_w			*(USHORT*)REG_W(EP0TXPLD)
#define	ep0stat_r			*(UCHAR*)REG_R(EP0STAT)
#define	ep0stat_w			*(USHORT*)REG_W(EP0STAT)

#define	ep2con_r			*(UCHAR*)REG_R(EP2CON)
#define	ep2con_w			*(USHORT*)REG_W(EP2CON)
#define	ep2tgl_r			*(UCHAR*)REG_R(EP2TGL)
#define	ep2tgl_w			*(USHORT*)REG_W(EP2TGL)
#define	ep2pld_r			*(UCHAR*)REG_R(EP2PLD)
#define	ep2pld_w			*(USHORT*)REG_W(EP2PLD)

#define	ep3con_r			*(UCHAR*)REG_R(EP3CON)
#define	ep3con_w			*(USHORT*)REG_W(EP3CON)
#define	ep3tgl_r			*(UCHAR*)REG_R(EP3TGL)
#define	ep3tgl_w			*(USHORT*)REG_W(EP3TGL)
#define	ep3pld_r			*(UCHAR*)REG_R(EP3PLD)
#define	ep3pld_w			*(USHORT*)REG_W(EP3PLD)


extern	EP_LIST_C		epC[];
extern	EP_LIST_V		epV[EP_MAX+1];
extern	const	Device_Desc		device_descriptor_basis;	/* Device Descriptor (Basis)	Rev.(AA52:BRZ-1554)	 */
extern	Device_Desc		device_descriptor;	/* Device Descriptor */
extern	Device_Request	device_request;		/* Device Request */
extern	USB_STATUS		usb_status;			/* Device Current Status */
extern	UCHAR			ep_stat[EP_MAX];	/* エンドポイント有効/無効状態 0:invalid 1:valid */	/* S990723 */





/*------------------------------------------------------*/
/*	マクロ												*/
/*------------------------------------------------------*/
/*----------------------------
      パケットレディ設定      
----------------------------*/
	/* EPn(n=0,1,2,3)の受信パケットレディリセット
		ep = EP0RX,EP1,EP2,EP3 */
	#define CLR_PKTRDY(ep)\
		pktrdy_w = ((USHORT)(epC[ep].b_recv_pktrdy))<<8;

	/* EPn(n=0,1,2,3)の送信パケットレディセット
		ep = EP0TX,EP1,EP2,EP3 */
	#define SET_PKTRDY(ep)\
		pktrdy_w = ((USHORT)(epC[ep].b_trns_pktrdy))<<8;

/*----------------------
      割り込み禁止      
----------------------*/
	/* EP0受信パケットレディ割り込み禁止 */
	#define DIS_EP0RX_PKTRDY_INT()\
		intenbl_w = ((USHORT)(intenbl_r & ~epC[EP0RX].b_pktrdy_int))<<8;

	/* EP0送信パケットレディ割り込み禁止 */
	#define DIS_EP0TX_PKTRDY_INT()\
		intenbl_w = ((USHORT)(intenbl_r & ~epC[EP0TX].b_pktrdy_int))<<8;

	/* EP0送受信パケットレディ割り込み禁止 */
	#define DIS_EP0TXRX_PKTRDY_INT()\
		intenbl_w = ((USHORT)(intenbl_r & ~(epC[EP0RX].b_pktrdy_int | epC[EP0TX].b_pktrdy_int)))<<8;

	/* EPn(n=1,2,3)パケットレディ割り込み禁止
		ep = EP1,EP2,EP3 */
	#define DIS_PKTRDY_INT(ep)\
		intenbl_w = ((USHORT)(intenbl_r & ~epC[ep].b_pktrdy_int))<<8;

	/* サスペンデッド割り込み禁止 */
	#define DIS_SUSPENDED_INT()\
		intenbl_w = ((USHORT)(intenbl_r & ~B_SUSPENDED_STATE_INT))<<8;


/*----------------------
      割り込み許可      
----------------------*/
	/* EP0受信パケットレディ割り込み許可 */
	#define ENA_EP0RX_PKTRDY_INT()\
		intenbl_w = ((USHORT)(intenbl_r | epC[EP0RX].b_pktrdy_int))<<8;

	/* EP0送信パケットレディ割り込み許可 */
	#define ENA_EP0TX_PKTRDY_INT()\
		intenbl_w = ((USHORT)(intenbl_r | epC[EP0TX].b_pktrdy_int))<<8;

	/* EPn(n=1,2,3)パケットレディ割り込み許可
		ep = EP1,EP2,EP3 */
	#define ENA_PKTRDY_INT(ep)\
		intenbl_w = ((USHORT)(intenbl_r | epC[ep].b_pktrdy_int))<<8;

	/* サスペンデッド割り込み許可 */
	#define ENA_SUSPENDED_INT()\
		intenbl_w = ((USHORT)(intenbl_r | B_SUSPENDED_STATE_INT))<<8;

	/* セットアップレディ,バスリセット,サスペンデッド割り込み許可(初期処理用) */
	#define ENA_SETUP_BUSRES_SUSPEND_INT()\
		intenbl_w = ((USHORT)(B_SETUP_RDY_INT | B_BUS_RESET_INT | B_SUSPENDED_STATE_INT))<<8;

	/* セットアップレディ,サスペンデッド割り込み許可(オリジナル) */
	#define ENA_SETUP_SUSPEND_INT()\
		intenbl_w = ((USHORT)(B_SETUP_RDY_INT | B_SUSPENDED_STATE_INT))<<8;

/*----------------------------
      割り込み要因クリア      
----------------------------*/
	/* USBバスリセット割り込みステートリセット */
	#define CLR_BUS_RESET_STATE()\
		dvcstat_w = ((USHORT)(dvcstat_r | B_BUS_RESET_CLR))<<8;

	/* セットアップレディリセット */
	#define CLR_SETUPRDY()\
	ep0stat_w = ((USHORT)(ep0stat_r | B_EP0_SETUP_RDY))<<8;

/*------------------------------
      割り込み要因チェック      
------------------------------*/
	/* セットアップレディ */
	#define SETUP_RDY_INT()\
		(intstat_r & B_SETUP_RDY_INT)

	/* EP1パケットレディ */
	#define EP1_PKTRDY_INT()\
		(intstat_r & B_EP1PKTRDY_INT)

	/* EP2パケットレディ */
	#define EP2_PKTRDY_INT()\
		(intstat_r & B_EP2PKTRDY_INT)

	/* EP3パケットレディ */
	#define EP3_PKTRDY_INT()\
		(intstat_r & B_EP3PKTRDY_INT)

	/* EP0受信パケットレディ */
	#define EP0_RXPKTRDY_INT()\
		(intstat_r & B_EP0RXPKTRDY_INT)

	/* EP0送信パケットレディ */
	#define EP0_TXPKTRDY_INT()\
		(intstat_r & B_EP0TXPKTRDY_INT)

	/* サスペンデッド */
	#define SUSPENDED_INT()\
		(intstat_r & B_SUSPENDED_STATE_INT)

	/* USBバスリセットアサート */
	#define USB_BUSRESET_ASS_INT()\
		(intstat_r & B_BUS_RESET_INT)


/*------------------------------------
      リモートウェイクアップ設定      
------------------------------------*/
	/* リモートウェイクアップビットのチェック */
	#define CHK_WAKEUP()\
		(dvcstat_r & B_REMOTE_WAKEUP)

	/* リモートウェイクアップビットのセット */
	#define SET_WAKEUP()\
		dvcstat_w = dvcstat_r | B_REMOTE_WAKEUP;


/*----------------------*/
/*      ストール設定    */
/*----------------------*/
	/* EP0のストールビットのセット */
	#define SET_STALL_EP0()\
		*epC[EP0].control_W = ((USHORT)(epC[EP0].b_stall))<<8;

	/* EPn(n=1,2,3)のストールビットのセット
		ep = EP1,EP2,EP3 */
	#define SET_STALL_EPn(ep)\
		*epC[ep].control_W = ((USHORT)(*epC[ep].control_R | epC[ep].b_stall))<<8;

	/* EP0のストールビットのクリア */
	#define CLR_STALL_EP0()\
		*epC[EP0].control_W = (USHORT)0;

	/* EPn(n=1,2,3)のストールビットのクリア
		ep = EP1,EP2,EP3 */
	#define CLR_STALL_EPn(ep)\
		*epC[ep].control_W = ((USHORT)(*epC[ep].control_R & ~epC[ep].b_stall))<<8;

	/* EPn(n=0,1,2,3)ストールビットの有無確認
		ep = EP0,EP1,EP2,EP3 */
	#define CHK_STALL_EPn(ep)\
		*epC[ep].control_R & epC[ep].b_stall


/*--------------------------
      トグルビット設定      
--------------------------*/
	/* EPn(n=0,1,2,3)のトグルビットのリセット
		ep = EP0,EP1,EP2,EP3 */
	#define CLR_TOGL_EPn(ep)\
		*epC[ep].datatgl_W = ((USHORT)(DATA_SEQUENCE_BIT))<<8;

	/* EP3のレートフィードバックをNormalに変更 */
	#define CLR_RATE_FEEDBACK()\
		*epC[EP3].control_W = ((USHORT)(*epC[EP3].control_R & 0x7F))<<8;


/*----------------------------------
      コンフィグレーション設定      
----------------------------------*/
	/* EPn(n=1,2,3)のコンフィグレーションビットセット
		ep = EP1,EP2,EP3 */
	#define SET_CONFIGBIT_EPn(ep)\
		*epC[ep].control_W = ((USHORT)(*epC[ep].control_R | CONFIG_BIT))<<8;

	/* Set Interface時，EPn(n=1,2,3)のコンフィグレーションビットセット
		転送方向の設定 & CONFIGURATION BIT ON & STALL ビット初期化を行う */
	#define SETINIT_CONFIGBIT_EPn(ep)\
		if (ep != EP3) {\
			*epC[ep].control_W = ((USHORT)((p_e_desc->bEndpointAddress & DEVICE_to_HOST) | CONFIG_BIT))<<8;\
		} else if (ep == EP3) {\
			*epC[ep].control_W = ((USHORT)(CONFIG_BIT))<<8;\
		}

	/* EPn(n=1,2,3)のコンフィグレーションビットリセット
		ep = EP1,EP2,EP3 */
	#define CLR_CONFIGBIT_EPn(ep)\
		*epC[ep].control_W = ((USHORT)(*epC[ep].control_R & ~CONFIG_BIT))<<8;

	/* すべてのEPn(n=1,2,3)のコンフィグレーションビットリセット
		ep = EP1,EP2,EP3 */
	#define CLR_CONFIGBIT_ALL_EPn()\
		*epC[EP1].control_W = ((USHORT)(*epC[EP1].control_R & ~CONFIG_BIT))<<8;\
		*epC[EP2].control_W = ((USHORT)(*epC[EP2].control_R & ~CONFIG_BIT))<<8;\
		*epC[EP3].control_W = ((USHORT)(*epC[EP3].control_R & ~CONFIG_BIT))<<8


/*------------------------------
      ペイロードサイズ設定      
------------------------------*/
	/* EPn(n=0,1,2,3)のペイロードサイズ設定
		ep = EP0TX,EP0RX,EP1,EP2,EP3 */
	#define SET_PAYLOAD_EPn(ep, size)\
		*epC[ep].payload_W = ((USHORT)size)<<8

	/* EPn(n=0,1,2,3)のペイロードサイズ取得
		ep = EP0TX,EP0RX,EP1,EP2,EP3 */
	#define GET_PAYLOAD_EPn(ep)\
		*epC[ep].payload_R


/*--------------------------
      転送方向チェック      
--------------------------*/
	/* EPn(n=1,2,3)の転送方向チェック HOST->DEVICE? YES:0x80/ NO:0x00
		ep = EP1,EP2,EP3 */
	#define CHK_EPn_HOST_TO_DEVICE(ep)\
		((*epC[ep].control_R & DEVICE_to_HOST))


/*--------------------
      FIFOクリア      
--------------------*/
	/* EPn(n=1,2,3)のFIFOレジスタクリア
		ep = EP1,EP2,EP3 */
	#define CLR_EPn_FIFO(ep)\
		clrfifo_w = ((USHORT)epC[ep].b_clrFIFO)<<8;


/*----------------------
      アドレス設定      
----------------------*/
	/* SET_ADDRESSリクエストによるアドレスをDVCADRレジスタに設定 */
	#define SET_ADDRESS_DATA(address)\
		dvcadr_w = ((USHORT)address)<<8;

	/* DVCADRレジスタから設定されているアドレス値を取得 */
	#define GET_ADDRESS_DATA()\
		dvcadr_r


/*---------------------------------------
      FIFOレジスタのアドレス取得         
---------------------------------------*/
	/* EPn(n=0,1,2,3)のライトFIFOレジスタのアドレスを取得
		ep = EP0TX,EP1,EP2,EP3 */
	#define GET_WFIFO_ADRS_EPn(ep)\
		epC[ep].fifo_W

	/* EPn(n=0,1,2,3)のリードFIFOレジスタのアドレスを取得
		ep = EP0RX,EP1,EP2,EP3 */
	#define GET_RFIFO_ADRS_EPn(ep)\
		epC[ep].fifo_R


/*--------------------------
      受信バイト数取得      
--------------------------*/
	/* EPn(n=0,1,2,3)の受信バイト数取得(１バイトデータ)
		ep = EP0RX,EP1,EP2,EP3 */
	#define GET_RECV_BYTE(ep)\
		*epC[ep].recv_byte_cnt


/*--------------------------------
      サスペンド時の省電設定      
--------------------------------*/
	/* サスペンド時に省電にする */
	#define ENA_POWER_DOWN()	/* ML60851Cには該当する設定無し */

	/* サスペンド時に省電にしない */
	#define DIS_POWER_DOWN()	/* ML60851Cには該当する設定無し */


/*------------------------------------
      デイバイスリクエストの取得      
------------------------------------*/
	#define GET_bmRequestType()		bmrequesttype_r;
	#define GET_bRequest()			brequest_r;
	#define GET_wValue()		 	(wValue)((wvalue_msb_r)<<8   | (wvalue_lsb_r));
	#define GET_wIndex()			(wIndex)(((windex_msb_r))<<8   | (windex_lsb_r));
	#define GET_wLength()			(wLength)((wlength_msb_r)<<8 | (wlength_lsb_r));


/*--------------------------------------
      エンドポイント転送方向の確認      
--------------------------------------*/
	/* Get_Statusでrecipiesntにエンドポイントが指定されたとき
	　USBコンフィグレーションレジスタ内の転送方向と
	　デバイスリクエストwIndex内の転送方向が一致しているか確認する
      ただし、EP0は転送方向のチェックは行わない */
	#define CHK_DIR_WINDEX_AND_CONTROL(ep)\
		( ep == EP0 || \
        ep != EP3 && (CHK_EPn_HOST_TO_DEVICE(ep) == \
		((UCHAR)device_request.wIndex & DEVICE_to_HOST)) ||\
		(ep == EP3 && ((UCHAR)device_request.wIndex & DEVICE_to_HOST)) )

	/* Set_Interfaceで送信用FIFOクリアを行うために
	　USBコンフィグレーションレジスタ内の転送方向が
	　Device to Hostか確認する */
	#define CHK_DIR_DEVICE_TO_HOST(ep)\
		((CHK_EPn_HOST_TO_DEVICE(ep) == DEVICE_to_HOST) || ep == EP3) 

/*--------------------------------------
	Pin function control				
--------------------------------------*/
	/* 極性選択レジスタの設定 */
	#define	SET_POLSEL()\
		polsel_w = 0x0000;
		
	/* DMA制御レジスタの設定 */
	#define	SET_DMACON()\
		dmacon_w = ((USHORT)(B_DMA_ENABLE | B_ADDRESS_MODE ))<<8;
		/*dmacon_w = ((USHORT)(B_DMA_ENABLE | B_ADDRESS_MODE | B_TRNS_SIZE))<<8;*/
		
	/* DMAインターバルの設定 */
	#define	SET_DMAINTVL()\
		dmaintvl_w = 0;

/*--------------------------------------------------------------------------*/
/*																			*/
/*																			*/
/*--------------------------------------------------------------------------*/
#define	CONT_BUF_SIZE		256		/* Buffer size for control communication*/
#define	EP_RX	2
#define	EP_TX	1
/*--------------------------------------------------------------------------*/
/*																			*/
/*																			*/
/*--------------------------------------------------------------------------*/

/*	=======================================================
	0.	Descriptorの初期化で用いるマクロ
	=======================================================
*/
/*
	Set_L_H()
	---------
	Low byte, High Byteの順に独立した2byteを定義する
	アライメントに沿わないワードの初期化を行う
*/
#define	Set_L_H(_val)	((_val) & 0xff), (((_val) >> 8) & 0xff)

/*
	WordSet()
	---------
	Endianの影響をワード型初期化を行う
	規格上のDescriptorの定義はLittleEndian形式
	したがってBigEndianマシンでは、バイト順を反転させる
*/
#define	WordSet(_val)	((((_val) & 0xff) << 8) | (((_val) >> 8) & 0xff))

#ifdef DEBUG_BANBA
#define	WordSet(_val)	(_val)
#endif

extern		UCHAR	 *pUsbReceiveStart;				/* Data Receive Buffer Pointer	*/
extern		UCHAR	 *pUsbTransmitStart;				/* Data Transmit Buffer Pointer	*/

#define		USB_STATUS_SET		'1'
#define		USB_STATUS_RESET	'0'
/*--------------------------------------------------------------------------*/
/*																			*/
/*	Function Prottype							 							*/
/*																			*/
/*--------------------------------------------------------------------------*/
void	bulk_rx(UCHAR *buf, uint size);
void	bulk_tx(UCHAR *buf, uint size);

void	UsbInitialize( void );
void	UsbSetStatusFromBoot( UCHAR *, UCHAR * );
void	UsbSoftReset( void );
void	UsbLSIReset( void );
BOOL	UsbTxStart(UCHAR *buf, UCHAR ep, uint size);
void	UsbRxStart(UCHAR *buf, UCHAR ep);
void	UsbSetCallback(UCHAR ep, void (*func)(UCHAR *, uint));

void	UsbReadDeviceRequests( void );
void	UsbReadFifo( char ep );
void	UsbWriteFifo( char ep );
	/*------------------------------------------------------------------*/
	/*	Rev.(AA52:BRZ-1554)		add function for Dual BRU				*/
	/*------------------------------------------------------------------*/
void	UsbMakeDeviceDescriptor( void );

