/*
 *
 */
#include "Arduino.h"
#include <LiquidCrystal.h>
#include <Ultrasonic.h>

const int rs = 2, en = 3, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
const int pir_pin = 9, ir_pin = 10, echo_pin = 11, trigger_pin = 12;
const int flow_time_pot = A0, distance_pot = A1;
const int solenoid_relay = 18, pump_relay = 19;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Ultrasonic ultrasonic(trigger_pin, echo_pin);

unsigned int distance_data, pir_data, ir_data;
unsigned int flow_time_pot_data, distance_pot_data;
unsigned int set_flow_time, set_flow_delay, set_distance;
unsigned int prev_set_flow_time, prev_set_distance;

bool sanitized = false;

void setup() {
	Serial.begin(9600);
	lcd.begin(16, 2);

	pinMode(pir_pin, INPUT);
	pinMode(ir_pin, INPUT);

	pinMode(solenoid_relay, OUTPUT);
	pinMode(pump_relay, OUTPUT);

	digitalWrite(solenoid_relay, HIGH);
	digitalWrite(pump_relay, HIGH);
}

void loop() {

	flow_time_pot_data = analogRead(flow_time_pot);
	distance_pot_data = analogRead(distance_pot);

	set_flow_time = map(flow_time_pot_data, 0, 1024, 0, 1024);
	set_flow_delay = set_flow_time * 5;
	set_distance = map(distance_pot_data, 0, 1000, 10, 200);

	distance_data = ultrasonic.distanceRead();
	pir_data = digitalRead(pir_pin);
	ir_data = digitalRead(ir_pin);

	Serial.print("Flow Time: ");
	Serial.print(flow_time_pot_data);
	Serial.print(", ");
	Serial.print(set_flow_time);
	Serial.print(", ");
	Serial.println(set_flow_delay);

	Serial.print("Distance : ");
	Serial.print(distance_pot_data);
	Serial.print(", ");
	Serial.print(set_distance);
	Serial.print(", ");
	Serial.println(distance_data);

	Serial.print("PIR : ");
	Serial.println(pir_data);

	Serial.print("IR : ");
	Serial.println(ir_data);

	if (set_flow_delay != prev_set_flow_time) {
		prev_set_flow_time = set_flow_delay;
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print(" AUTO FLOW TIME ");
		lcd.setCursor(0, 1);
		lcd.print("     " + String(set_flow_delay) + "msec    ");
		delay(1000);
	}

	if (set_distance != prev_set_distance) {
		prev_set_distance = set_distance;
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print(" HAND DISTANCE  ");
		lcd.setCursor(0, 1);
		lcd.print("     " + String(set_distance) + " cm     ");
		delay(1000);
	}

	if (distance_data != 0 && distance_data < set_distance) {
		sanitize("Ultrasonic");
		Serial.println("~~~~~~~~~~~~~~~Ultrasonic detected");
	} else if (pir_data == HIGH) {
		sanitize("PIR Sensor");
		Serial.println("***************PIR detected");
	} else if (ir_data == LOW) {
		Serial.println("~~~~~~~~~~~~~~~IR detected");
		sanitize("IR Sensor");
	}else{
		sanitized = false;
	}

	lcd.setCursor(0, 0);
	lcd.print(" AUTO SANITIZER ");
	lcd.setCursor(0, 1);
	lcd.print("Place hand below");
}

void sanitize(String sen) {
	if (sanitized == false) {
		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print("SANITIZING HANDS");

		digitalWrite(solenoid_relay, LOW);
		delay(50);
		digitalWrite(pump_relay, LOW);
		delay(set_flow_delay);
		digitalWrite(solenoid_relay, HIGH);
		digitalWrite(pump_relay, HIGH);
		delay(1000);

		lcd.clear();
		lcd.setCursor(0, 0);
		lcd.print("THANKS FOR USING");
		lcd.setCursor(0, 1);
		lcd.print("SEN: " + sen);
		sanitized = true;
		delay(1000);
	}
}
