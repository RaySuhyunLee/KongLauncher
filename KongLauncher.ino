/*
 * Turret source code
 */

/*
 * Hardware Serial(0, 1) is used for drone - launcher communication.
 * SoftwareSerial(2, 3) is used for imu - launcher communication.
 */
SoftwareSerial imu(2, 3);	// (rxPin, txPin)

Servo missile_trigger;
#define TRIGGER_PIN 4;
#define SERVO_VALUE_FIRE 1000
#define SERVO_VALUE_IDLE 1000

bool is_armed;
uint8_t control_mode;
bool is_missile_ready;

void setup() {
	missile_trigger.attach(TRIGGER_PIN);

	Serial.begin(115200);
	imu.begin(115200);
}

void loop() {
	if (Serial.available() > 0) {
		byte buf;
		const buffer_size = 10;
		byte read_buffer[buffer_size];
		int cnt;
		do {
			buf = Serial.read();
			read_buffer[cnt++] = buf;
			if (cnt >= buffer_size) {
				cnt = 0;	// something went wrong. dont use buffer
				break;
			}
		} while(buf != 0xFF);

		/* parse command */
		if (cnt >= 0) {
			switch(read_buffer[0]) {
				case CMD_ARM:
					is_armed = true;
					break;
				case CMD_DISARM:
					is_armed = false;
					break;
				case CMD_MODE:
					change_mode(param(read_buffer, 0));
					break;
				case CMD_MOVE:
					move_turret(param(read_buffer, 0), param(read_buffer, 1))
					break;
				case CMD_FIRE:
					fire();
					break;
			}
		}
	}
}

void fire() {
	if (!is_armed || !is_missile_ready)	// only fire when armed
		return;

	is_missile_ready = false;	
	missile_trigger.writeMicroseconds(SERVO_VALUE_FIRE);
	delay(70);
	missile_trigger.writeMicroseconds(SERVO_VALUE_IDLE);
	reload();
}

void reload() {
	is_missile_ready = true;
}
