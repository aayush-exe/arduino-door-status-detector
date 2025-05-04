# doordetector
Simple Arduino/ESP32 powered device to alert when a door is opened/closed through Discord

![Screenshot 2025-05-04 at 1 41 25 PM](https://github.com/user-attachments/assets/a3234485-bd1f-4a3c-9957-ef81ef98077c)

Have a club/shared room/any shared space and want to know when it's open? This simple device detects when a door is opened and closed, both with toggle and with live state modes.
Uses a limit switch (can be changed to other detection methods like beam breakers w/ simple coding) and a Wi-Fi powered Arduino or ESP32 (I used Arduino Nano ESP32 in this)

-> toggle: door state toggled with every limit switch open/close
-> live state: status open when limit switch open, closed when limit switch closed

How to do this:

1. make sure ur Arduino has WiFi
2. Wire a limit switch (or whatever detection method you want) to the board, setup in code
3. Set up your WiFi's name and password (if it has no password, leave it blank)
4. On the server and channel you want to have it in, go to Server Settings -> Integrations -> Webhooks
5. Click "New Webhook", then click on the webhook you just created and change the name and profile picture to whatever you want
6. Click "Copy Webhook URL" and in the Arduino code, replace the channel id and token as specified
7. Set your delay at the top of the code (example has 60 second delay between door being opened/closed and message being sent)
8. Upload, plug in the arduino, and enjoy

Follow for more tips
