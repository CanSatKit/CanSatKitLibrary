#ifndef BMP280_h
#define BMP280_h

#include "Arduino.h"

namespace CanSatKit {

/**
 * @brief BMP280 pressure sensor base class.
 */
class BMP280
{
	public:
		/**
		 * @brief Construct a new BMP280 object
		 */
		BMP280();

		/**
		 * @brief Initialize sensor and calibrate.
		 * 
		 * @return `true` if initialization succeeded, `false` otherwise (eg. i2C connection problem)
		 */
		bool begin();
		
		/**
		 * @brief Set oversampling ratio.
		 * Should be one of the following: 0, 1, 2, 3, 4, 16.
		 * 
		 * \rst
		 * +---------------+-----------------------+
         * | Oversampling  | Conversion time (ms)  |
         * +===============+=======================+
         * | 0             |        8              |
         * +---------------+-----------------------+
		 * | 1             |        10             |
         * +---------------+-----------------------+
		 * | 2             |        15             |
         * +---------------+-----------------------+
		 * | 3             |        24             |
         * +---------------+-----------------------+
		 * | 4             |        45             |
         * +---------------+-----------------------+
		 * | 16            |        80             |
         * +---------------+-----------------------+
		 * 
		 * \endrst
		 * 
		 * Higher oversampling means longer measurement, but more accurate result
		 * 
		 * @param oversampling ratio
		 */
		void setOversampling(uint8_t oversampling);

		/**
		 * @brief Get previously set oversampling.
		 * 
		 * @return uint8_t oversampling set
		 */
		uint8_t getOversampling();

		/**
		 * @brief Perform temperature and pressure measurement.
		 * This is blocking function (return always new value).
		 * For non-blocking usage, see startMeasurment() and readTemperatureAndPressure()
		 * 
		 * @param T temperature read from the device
		 * @param P pressure read from the device
		 * @return bool Measurement status
		 */
		bool measureTemperatureAndPressure(double& T, double& P);


		/**
		 * @brief Begin a measurement cycle.
		 * This function returns the delay before result will be available to read.
		 * 
		 * @return unsigned int delay to read measurement result (ms)
		 */
		unsigned int startMeasurment();

		/**
		 * @brief Read temperature and pressure.
		 * Use it after startMeasurment() and proper delay.
		 * 
		 * @param T temperature read from the device
		 * @param P pressure read from the device
		 * @return Measurement status
		 */
		bool readTemperatureAndPressure(double& T, double& P);

	private:
		bool calcTemperature(double &T, double &uT);			
		bool calcPressure(double &P, double uP);
	
		bool readCalibration();
			// Retrieve calibration data from device:
			// The BMP280 includes factory calibration data stored on the device.
			// Each device has different numbers, these must be retrieved and
			// used in the calculations when taking measurements.

		bool readInt(char address, double &value);
			// read an signed int (16 bits) from a BMP280 register
			// address: BMP280 register address
			// value: external signed int for returned value (16 bits)
			// returns 1 for success, 0 for fail, with result in value

		bool readUInt(char address, double &value);
			// read an unsigned int (16 bits) from a BMP280 register
			// address: BMP280 register address
			// value: external unsigned int for returned value (16 bits)
			// returns 1 for success, 0 for fail, with result in value

		bool readBytes(unsigned char *values, char length);
			// read a number of bytes from a BMP280 register
			// values: array of char with register address in first location [0]
			// length: number of bytes to read back
			// returns 1 for success, 0 for fail, with read bytes in values[] array
			
		bool writeBytes(unsigned char *values, char length);
			// write a number of bytes to a BMP280 register (and consecutive subsequent registers)
			// values: array of char with register address in first location [0]
			// length: number of bytes to write
			// returns 1 for success, 0 for fail
		
		bool getUnPT(double &uP, double &uT);	
			//get uncalibrated UP and UT value.
	
				
		//int dig_T2 , dig_T3 , dig_T4 , dig_P2 , dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9; 
		//unsigned int dig_P1 , dig_T1 ;
		double dig_T1, dig_T2 , dig_T3 , dig_T4 , dig_P1, dig_P2 , dig_P3, dig_P4, dig_P5, dig_P6, dig_P7, dig_P8, dig_P9; 
		uint8_t oversampling;
		double t_fine;
		char error;
};

#define BMP280_ADDR 0x76 // 7-bit address

#define	BMP280_REG_CONTROL 0xF4
#define	BMP280_REG_RESULT_PRESSURE 0xF7			// 0xF7(msb) , 0xF8(lsb) , 0xF9(xlsb) : stores the pressure data.
#define BMP280_REG_RESULT_TEMPRERATURE 0xFA		// 0xFA(msb) , 0xFB(lsb) , 0xFC(xlsb) : stores the temperature data.

#define	BMP280_COMMAND_TEMPERATURE 0x2E
#define	BMP280_COMMAND_PRESSURE0 0x25  			 
#define	BMP280_COMMAND_PRESSURE1 0x29  			
#define	BMP280_COMMAND_PRESSURE2 0x2D    
#define	BMP280_COMMAND_PRESSURE3 0x31    
#define	BMP280_COMMAND_PRESSURE4 0x5D    
#define	BMP280_COMMAND_OVERSAMPLING_MAX 0xF5

};  // namespace CanSatKit

#endif