# The Design and Construction of a Wearable to Prevent Students from Falling Asleep in Class
synopsys '23 project

We are trying to solve the problem of students sleeping in class, which impacts performance and learning. We have engineered a device that can wake people up from sleeping in class. We decided to test the device using a higher threshold BPM, as it would be easier to run more trials with it instead of actually sleeping to test the device. Our human subject would run until his heart rate was 150 BPM then put on the device. If the heart rate dropped below 90 bpm and the accelerometer did not detect any motion greater than 10 units on any axis for 15 seconds, the vibrator would turn on. While this 15 second waiting period made getting trials easier, we think the data would be more accurate if the device waited for a longer time. However, this would make getting large amounts of data impossible. We chose to set the threshold of low bpm at 90 because it is 60% of 150 bpm, 90 bpm simulates sleep because in sleep, heart rate usually falls 20 to 40 percent. The average time the device took to trigger over our 50 tests was 3 minutes and 17 seconds, with only 2 of our 50 data points being outliers. While our device is reliable, it could be improved. A more precise pulse sensor and a SpO2 sensor could improve our device. This device and code could be part of the omnipresent smartwatches that everyone wears, which could benefit many people. 








