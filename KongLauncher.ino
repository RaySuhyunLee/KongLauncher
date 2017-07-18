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

#define CYLINDER_MOTOR_PIN 5

Servo pitch_servo;
#define PITCH_SERVO_PIN 7;
Servo yaw_servo;
#define YAW_SERVO_PIN 8;

bool __is_armed;
uint8_t __control_mode;
bool __is_missile_ready;

void setup() {
	// initialize output pins
	pinMode(output, CYLINDER_MOTOR_PIN);
	missile_trigger.attach(TRIGGER_PIN);
	pitch_servo.attach(PITCH_SERVO_PIN);
	yaw_servo.attach(YAW_SERVO_PIN);

	Serial.begin(115200);
	imu.begin(115200);
}

void change_mode(int mode);
void move_turret(double pitch, double yaw);
void fire();
void reload();

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
					move_turret(
							param_double(read_buffer, 0) / 100.0, 
							param_double(read_buffer, 1) / 100.0
							);
					break;
				case CMD_FIRE:
					fire();
					break;
			}
		}
	}
}

void change_mode(uint8_t mode) {
	if (mode == MODE_MANUAL || mode == MODE_AUTO) {
		__control_mode = mode;
	}
}

void move_turret(double pitch, double yaw) {
	if (__control_mode == MODE_AUTO) {
		__desired_pitch = constrain(pitch * 500 / 45, -500, 500) + 1500;
		__desired_yaw = constrain(yaw * 500 / 45, -500, 500) + 1500;
	}
}

void fire() {
	if (!__is_armed || !__is_missile_ready)	// only fire when armed
		return;

	__is_missile_ready = false;	
	missile_trigger.writeMicroseconds(SERVO_VALUE_FIRE);
	delay(70);
	missile_trigger.writeMicroseconds(SERVO_VALUE_IDLE);
	reload();
}

void reload() {
	__is_missile_ready = true;
}
