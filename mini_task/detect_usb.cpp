#include <iostream>
#include <libusb-1.0/libusb.h>

#define IDUSB1 17152
#define IDUSB2 4660

bool checkUSB(libusb_device **dev, libusb_context *ctx, bool & fl1, bool & fl2);

void print();

int main()
{
	libusb_device  **devs;
	libusb_context *ctx = NULL;
	libusb_init(&ctx);

	libusb_set_debug(ctx, 3);
	bool fl1 = 0, fl2 = 0, flc1, flc2, fl = 0;

	while(1)
	{
		checkUSB(devs, ctx, flc1, flc2);
		if ( !( fl1 ==flc1 && fl2 == flc2 ))
		{
			fl = 1;
			fl1 = flc1;
			fl2 = flc2;

		}
		if(fl)
		{
			std::cout << "CHANGE" << std::endl;
			fl = 0;
		}

		//std::cout << flc1 << fl1 <<std::endl;
	}


}

void print()
{
	std::cout << "change";
}

bool checkUSB(libusb_device **dev, libusb_context *ctx, bool & fl1, bool & fl2)
{
	fl1 = false;
	fl2 = false;

	int N = libusb_get_device_list(ctx, &dev);
	libusb_device_descriptor desc;

	for(int i = 0 ; i < N; ++ i)
	{
		libusb_get_device_descriptor(dev[i], &desc);
		if((((int)desc.idProduct == IDUSB1) && (fl1 = true))){}
		if((((int)desc.idProduct == IDUSB2) && (fl2 = true))){}



		//std::cout << (int)desc.idProduct << " " << fl2 << std::endl;
	}

	libusb_free_device_list(dev, 1);
	return 1;

}


