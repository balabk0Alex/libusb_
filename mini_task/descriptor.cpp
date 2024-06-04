#include <iostream>
#include <libusb-1.0/libusb.h>


#define IDUSB 4660


int main()
{
	libusb_device ** devs;
	libusb_device * myUSB = NULL;

	libusb_context *ctx;


	libusb_device_descriptor dev_desc;
	libusb_config_descriptor *config;

	int err = libusb_init(&ctx);

	libusb_set_debug(ctx, 3);

	size_t cout_device = libusb_get_device_list(ctx, &devs);


	for(int i = 0; i < cout_device; ++i)
	{
		libusb_get_device_descriptor(devs[i], &dev_desc);
		if(dev_desc.idProduct == IDUSB)
		{
			myUSB = devs[i];
			break;
		}
	}
	if (myUSB != NULL)
	{
		libusb_get_config_descriptor(myUSB, 0, &config);

		std::cout << "max power: " << (int)config->MaxPower << std::endl;
		std::cout << "NumInterfaces" <<(int)config->bNumInterfaces << std::endl;
		std::cout << "Configuration" <<(int) config->iConfiguration << std::endl;
		std::cout << "Attributes" <<(int) config->bmAttributes << std::endl;

		std::cout << "COMPLETE";
	}
	else
	{
		std::cout << "ERROR";
	}
	libusb_free_device_list(devs, 1);
	libusb_exit(ctx);

}
