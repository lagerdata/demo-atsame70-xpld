from lager import lager
import time
import math



def main():
	gateway = lager.Lager()
	checkLineVoltages(gateway)
	checkLedBlinks(gateway)




def checkLineVoltages(gateway):
	#Verify Line Voltages
	resp = gateway.adc.read(output='mv')
	#This WILL pass
	# if abs((diff3 := (3.3 - resp[0][0]))) > 0.2:
	# 	raise SystemExit(f"3.3V Rail out of bounds by {diff3}")
	# if abs((diff5 := (5 - resp[0][1]))) > 0.2:
	# 	raise SystemExit(f"5V Rail out of bounds by {diff5}")

	#This WILL fail
	if abs((diff3 := (3.3 - resp[0][0]))) > 0.01:
		raise SystemExit(f"3.3V Rail out of bounds by {diff3}")
	if abs((diff5 := (5 - resp[0][1]))) > 0.01:
		raise SystemExit(f"5V Rail out of bounds by {diff5}")

	print(f"3.3V rail is {3.3 + diff3}")
	print(f"5V rail is {5 + diff5}")

def checkLedBlinks(gateway):
	#Connect to device so we can reset it
	device = gateway.connect("atsame70", interface="ftdi", transport="swd")
	start_time = time.time()
	timeout = start_time + 16	
	blink_count = 0;
	#put device into reset halt state - no code running
	device.reset(halt=True)

	#measure pin off state
	led_pin_state = gateway.gpio.read(0)

	#start running code
	#verify that pin is blinking as expected
	device.reset()
	while True:
		if time.time() > timeout:
			raise SystemExit("Blink Timed Out")
		new_pin_state = gateway.gpio.read(0)
		if new_pin_state != led_pin_state:
			blink_count = blink_count + 1
			led_pin_state = new_pin_state
			print(f"Pin state changed to {led_pin_state}")
			print(f"Blink Count:{blink_count}")
		if blink_count == 10:
			if (time.time() - start_time) > 5.1:
				raise SystemExit("1s blinks are broken")
		if blink_count == 20:
			if(time.time() - start_time) > 15.1:
				raise SystemExit("2s blinks are broken")
			break;

	print("Brilliant!")
if __name__ == '__main__':
	main()