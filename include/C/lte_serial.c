#include <stdlib.h>
#include <string.h>

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/efm32/cmu.h>
#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/cdc.h>

struct SerialHeaderStruct {
    bool isConnected;
    usbd_device* usbDevice;
    uint8_t controlBuffer[128];
    char** lines;
    char* line;
    int linesSize;
    int lineSize;
    int returnedLines;
} SerialHeader;

void usb_isr() {
    usbd_poll(SerialHeader.usbDevice);
}

const struct usb_device_descriptor serialUSBDescriptor = {
    .bLength = USB_DT_DEVICE_SIZE,
    .bDescriptorType = USB_DT_DEVICE,
    .bcdUSB = 0x0200,
    .bDeviceClass = USB_CLASS_CDC,
    .bDeviceSubClass = 0,
    .bDeviceProtocol = 0,
    .bMaxPacketSize0 = 64,
    .idVendor = 4617,
    .idProduct = 28849,
    .bcdDevice = 257,
    .iManufacturer = 1,
    .iProduct = 2,
    .iSerialNumber = 3,
    .bNumConfigurations = 1,
};

const struct usb_endpoint_descriptor serialCommEndpoint[] = {
    {
        .bLength = USB_DT_ENDPOINT_SIZE,
        .bDescriptorType = USB_DT_ENDPOINT,
        .bEndpointAddress = 0x83,
        .bmAttributes = USB_ENDPOINT_ATTR_INTERRUPT,
        .wMaxPacketSize = 16,
        .bInterval = 255,
    }
};

const struct usb_endpoint_descriptor serialDataEndpoint[] = {
    {
        .bLength = USB_DT_ENDPOINT_SIZE,
        .bDescriptorType = USB_DT_ENDPOINT,
        .bEndpointAddress = 0x01,
        .bmAttributes = USB_ENDPOINT_ATTR_BULK,
        .wMaxPacketSize = 64,
        .bInterval = 1,
    }, {
        .bLength = USB_DT_ENDPOINT_SIZE,
        .bDescriptorType = USB_DT_ENDPOINT,
        .bEndpointAddress = 0x82,
        .bmAttributes = USB_ENDPOINT_ATTR_BULK,
        .wMaxPacketSize = 64,
        .bInterval = 1,
    }
};

const struct {
    struct usb_cdc_header_descriptor header;
    struct usb_cdc_call_management_descriptor call_mgmt;
    struct usb_cdc_acm_descriptor acm;
    struct usb_cdc_union_descriptor cdc_union;
} __attribute__((packed)) serialCDCACMDescriptors = {
    .header = {
        .bFunctionLength = sizeof(struct usb_cdc_header_descriptor),
        .bDescriptorType = CS_INTERFACE,
        .bDescriptorSubtype = USB_CDC_TYPE_HEADER,
        .bcdCDC = 0x0110,
    },
    .call_mgmt = {
        .bFunctionLength = sizeof(struct usb_cdc_call_management_descriptor),
        .bDescriptorType = CS_INTERFACE,
        .bDescriptorSubtype = USB_CDC_TYPE_CALL_MANAGEMENT,
        .bmCapabilities = 0,
        .bDataInterface = 1,
    },
    .acm = {
        .bFunctionLength = sizeof(struct usb_cdc_acm_descriptor),
        .bDescriptorType = CS_INTERFACE,
        .bDescriptorSubtype = USB_CDC_TYPE_ACM,
        .bmCapabilities = 6,
    },
    .cdc_union = {
        .bFunctionLength = sizeof(struct usb_cdc_union_descriptor),
        .bDescriptorType = CS_INTERFACE,
        .bDescriptorSubtype = USB_CDC_TYPE_UNION,
        .bControlInterface = 0,
        .bSubordinateInterface0 = 1,
     }
};

const struct usb_interface_descriptor serialCommIFace[] = {
    {
        .bLength = USB_DT_INTERFACE_SIZE,
        .bDescriptorType = USB_DT_INTERFACE,
        .bInterfaceNumber = 0,
        .bAlternateSetting = 0,
        .bNumEndpoints = 1,
        .bInterfaceClass = USB_CLASS_CDC,
        .bInterfaceSubClass = USB_CDC_SUBCLASS_ACM,
        .bInterfaceProtocol = USB_CDC_PROTOCOL_AT,
        .iInterface = 0,
        .endpoint = serialCommEndpoint,
        .extra = &serialCDCACMDescriptors,
        .extralen = sizeof(serialCDCACMDescriptors)
    }
};

const struct usb_interface_descriptor serialDataIFace[] = {
    {
        .bLength = USB_DT_INTERFACE_SIZE,
        .bDescriptorType = USB_DT_INTERFACE,
        .bInterfaceNumber = 1,
        .bAlternateSetting = 0,
        .bNumEndpoints = 2,
        .bInterfaceClass = USB_CLASS_DATA,
        .bInterfaceSubClass = 0,
        .bInterfaceProtocol = 0,
        .iInterface = 0,
        .endpoint = serialDataEndpoint,
    }
};

const struct usb_interface serialIFaces[] = {
    {
        .num_altsetting = 1,
        .altsetting = serialCommIFace,
    }, {
        .num_altsetting = 1,
        .altsetting = serialDataIFace,
    }
};

const struct usb_config_descriptor serialConfig = {
    .bLength = USB_DT_CONFIGURATION_SIZE,
    .bDescriptorType = USB_DT_CONFIGURATION,
    .wTotalLength = 0,
    .bNumInterfaces = 2,
    .bConfigurationValue = 1,
    .iConfiguration = 0,
    .bmAttributes = 0x80,
    .bMaxPower = 0x32,
    .interface = serialIFaces,
};

enum usbd_request_return_codes serialControlRequest(
    usbd_device* usbd_dev,
    struct usb_setup_data* req,
    uint8_t** buf,
    uint16_t* len,
    void (**complete)(usbd_device* usbd_dev, struct usb_setup_data* req)
) {
    (void) complete;
    (void) buf;
    (void) usbd_dev;

    switch(req->bRequest) {
    case USB_CDC_REQ_SET_CONTROL_LINE_STATE:
        SerialHeader.isConnected = req->wValue & 1;
        return USBD_REQ_HANDLED;

    case USB_CDC_REQ_SET_LINE_CODING:
        if (*len < sizeof(struct usb_cdc_line_coding)) {
            return 0;
        }

        return USBD_REQ_HANDLED;
    }
    return 0;
}

void sendSerial(const char* s) {
    if (SerialHeader.isConnected) {
        usbd_ep_write_packet(SerialHeader.usbDevice, 0x82, s, strnlen(s, 64));
        for (int i = 0; i < 2000; i++) {
            asm("mov r1, #6");
            asm("retry:");
            asm("sub r1, #1");
            asm("bne retry");
            asm("nop");
        }
    }
}

void serialCDCACMCallback(usbd_device* usbd_dev, uint8_t ep) {
    (void) ep;

    char buf[64];
    uint32_t len = usbd_ep_read_packet(usbd_dev, 0x01, buf, sizeof(buf));
    usbd_ep_write_packet(SerialHeader.usbDevice, 0x82, buf, len);
    for (uint32_t i = 0; i < len; i++) {
        if ((SerialHeader.lineSize == 255) || (buf[i] == '\r') || (buf[i] == '\n')) {
            SerialHeader.line[SerialHeader.lineSize] = 0;

            SerialHeader.linesSize++;
            SerialHeader.lines = (char**) realloc(SerialHeader.lines, SerialHeader.linesSize * sizeof(char*));\
            SerialHeader.lines[SerialHeader.linesSize-1] = SerialHeader.line;

            SerialHeader.lineSize = 0;
            SerialHeader.line = (char*) malloc(256 * sizeof(char));

            sendSerial("\r\n");
            break;
        }
        SerialHeader.line[SerialHeader.lineSize] = buf[i];
        SerialHeader.lineSize++;
    }
}

void cdcacmConfig(usbd_device* usbd_dev, uint16_t wValue) {
    (void) wValue;

    usbd_ep_setup(usbd_dev, 0x01, USB_ENDPOINT_ATTR_BULK, 64, serialCDCACMCallback);
    usbd_ep_setup(usbd_dev, 0x82, USB_ENDPOINT_ATTR_BULK, 64, 0);
    usbd_ep_setup(usbd_dev, 0x83, USB_ENDPOINT_ATTR_INTERRUPT, 16, 0);

    usbd_register_control_callback(
        usbd_dev,
        USB_REQ_TYPE_CLASS | USB_REQ_TYPE_INTERFACE,
        USB_REQ_TYPE_TYPE | USB_REQ_TYPE_RECIPIENT,
        serialControlRequest
    );
}

bool serialConnected() {
    return SerialHeader.isConnected;
}

char* readSerial() {
    if (SerialHeader.returnedLines == SerialHeader.linesSize) {
        return NULL;
    }
    SerialHeader.returnedLines++;
    return SerialHeader.lines[SerialHeader.returnedLines-1];
}

const char* usb_strings[] = {
    "Tomu",
    "OpticSpy Transmitter",
    "70mu-5py",
};

void Serial() {
    SerialHeader.isConnected = false;
    SerialHeader.usbDevice = 0;

    SerialHeader.lines = (char**) malloc(sizeof(char*));
    SerialHeader.line = (char*) malloc(256 * sizeof(char));
    SerialHeader.linesSize = 0;
    SerialHeader.lineSize = 0;
    SerialHeader.returnedLines = 0;

    cmu_periph_clock_enable(CMU_GPIO);

    SerialHeader.usbDevice = usbd_init(
        &efm32hg_usb_driver,
        &serialUSBDescriptor,
        &serialConfig,
        usb_strings,
        3,
        SerialHeader.controlBuffer,
        sizeof(SerialHeader.controlBuffer)
    );

    usbd_register_set_config_callback(SerialHeader.usbDevice, cdcacmConfig);
    nvic_enable_irq(NVIC_USB_IRQ);
}
