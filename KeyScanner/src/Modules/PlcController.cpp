#include "PlcController.hpp"

#include <iostream>

void PlcController::build_plcController()
{
	rw::hoem::ModbusDeviceRtuCfg config;
	config.device = "COM3";           // 使用 COM3 串口
	config.baud = 115200;               // 波特率 9600
	config.parity = 'N';              // 无校验
	config.dataBit = 8;               // 8 数据位
	config.stopBit = 1;               // 1 停止位
	config.baseAddress = 0;           // 无地址偏移

	plcController = std::make_shared<rw::hoem::ModbusDevice>(config);

	bool isConnect = plcController->connect();

	if (isConnect)
	{
		plcControllerScheduler = std::make_shared<rw::hoem::ModbusDeviceScheduler>(plcController);

		std::cout << "PLC connected successfully." << std::endl;


		/*while (true)
		{
			auto isSuccess = plcControllerScheduler->readRegister32Async(700,
				 rw::hoem::Endianness::LittleEndian,
				3, std::chrono::milliseconds(1000));

			plcControllerScheduler->wait();
			try
			{
				isSuccess.get();
			}
			catch (...)
			{
				auto result = plcController->reconnect();
				std::cout << "PLC：" << result << std::endl;
			}
		}*/
	}

	/*bool isConnect = plcController->connect();
	if (isConnect)
	{
		std::cout << "PLC connected successfully." << std::endl;
	}

	auto abc = plcController->writeRegister(700, 123u, rw::hoem::Endianness::LittleEndian);
	if (abc)
	{
		
	}

	bool isChuFa = false;

	auto bcd = plcController->readCoil(188, isChuFa);
	if (isChuFa && bcd)
	{
		std::cout << "线圈触发!" << std::endl;

		auto bcd = plcController->writeCoil(188, false);
	}*/
}

void PlcController::destroy_plcController()
{
	if (plcController)
	{
		plcController.reset();
	}
}
