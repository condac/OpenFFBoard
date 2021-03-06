#include "usb_device.h"
#include "usbd_core.h"
#include "usbd_desc.h"
#include "usbd_cdc.h"
#include "usbd_cdc_if.h"

#include "constants.h"
#include "usbd_composite.h"
#include "usbd_customhid.h"

USBD_HandleTypeDef hUsbDeviceFS;

USBD_ClassTypeDef* handles[2];


void USB_DEVICE_Init(uint8_t composite)
{


	if(composite == 1){


		handles[CDC_IDX] = &USBD_CDC;
		handles[HID_IDX] = &USBD_CUSTOM_HID;

		// Base Descriptor
		USB_ConfigDescType base_desc = {
			/*Configuration Descriptor*/
			0x09,   /* bLength: Configuration Descriptor size */
			USB_DESC_TYPE_CONFIGURATION,      /* bDescriptorType: Configuration */
			0x00,                /* wTotalLength:no of returned bytes. Is set later by composite */
			0x03,   /* bNumInterfaces */
			0x01,   /* bConfigurationValue: Configuration value */
			0x02,   /* iConfiguration: Index of string descriptor describing the configuration */
			0xC0,   /* bmAttributes: self powered */
			0x32,   /* MaxPower 100 mA */

		};

		USBD_Init(&hUsbDeviceFS, &FS_Desc_Composite, DEVICE_FS);

		// Add descriptors and class functions to composite device
		USBD_Composite_Set_Classes(handles,2,&base_desc);

		// Define endpoints

		//HID
		USBD_Composite_EPIN_To_Class(CUSTOM_HID_EPIN_ADDR, HID_IDX);
		USBD_Composite_EPOUT_To_Class(CUSTOM_HID_EPOUT_ADDR, HID_IDX);
		USBD_Composite_InterfaceToClass(HID_INTERFACE,HID_IDX);

		// CDC
		USBD_Composite_EPIN_To_Class(CDC_CMD_EP, CDC_IDX);
		USBD_Composite_EPIN_To_Class(CDC_IN_EP, CDC_IDX);
		USBD_Composite_EPIN_To_Class(CDC_OUT_EP, CDC_IDX);

		USBD_Composite_InterfaceToClass(CDC_INTERFACE,CDC_IDX);
		USBD_Composite_InterfaceToClass(CDC_INTERFACE_DATA,CDC_IDX);


		USBD_RegisterClass(&hUsbDeviceFS, &USBD_Composite);

		//USBD_Composite_RegisterInterface(&hUsbDeviceFS);
		USBD_CDC_RegisterInterface(&hUsbDeviceFS, &USBD_Interface_fops_FS);
		USBD_CUSTOM_HID_RegisterInterface(&hUsbDeviceFS, &USBD_CustomHID_fops_FS);

		USBD_Start(&hUsbDeviceFS);
		//USBD_LL_Start(&hUsbDeviceFS);

	}else{
		USBD_Init(&hUsbDeviceFS, &FS_Desc, DEVICE_FS);

		USBD_RegisterClass(&hUsbDeviceFS, &USBD_CDC);

		USBD_CDC_RegisterInterface(&hUsbDeviceFS, &USBD_Interface_fops_FS);

		USBD_Start(&hUsbDeviceFS);
	}





}
