/*
 * Turret source code
 */

/*
 * Hardware Serial(0, 1) is used for drone - launcher communication.
 * SoftwareSerial(2, 3) is used for imu - launcher communication.
 */
SoftwareSerial imu(2, 3);	// (rxPin, txPin)

void setup() {
	Serial.begin(115200);
	imu.begin(115200);
}

void loop() {
	if (Serial.available() > 0) {
		Serial.readBytes();
	}
}
