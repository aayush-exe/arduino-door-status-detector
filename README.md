# doordetector
Simple Arduino/ESP32 powered device to alert when a door is opened/closed through Discord

![Screenshot 2025-05-04 at 1 41 25 PM](https://github.com/user-attachments/assets/a3234485-bd1f-4a3c-9957-ef81ef98077c)

Have a club/shared room/any shared space and want to know when it's open? This simple device detects when a door is opened and closed, both with toggle and with live state modes.
Uses a limit switch (can be changed to other detection methods like beam breakers w/ simple coding) and a Wi-Fi powered Arduino or ESP32 (I used Arduino Nano ESP32 in this)

I was inspired to make this project as my project team's lab was notorious for being left shut with no update from anyone. Thanks to this invention I always know when I can show up

-> toggle: door state toggled with every limit switch open/close

-> live state: status open when limit switch open, closed when limit switch closed

How to do this:

1. make sure ur Arduino has WiFi (esp32 should have it built-in)
2. Wire a limit switch (or whatever detection method you want) to the board, and update the pin number in code
3. Change the WiFi SSID and password to your own network's (if it has no password, leave the password field blank)
4. On the Discord server and channel you want to have the bot send messages in, go to Server Settings -> Integrations -> Webhooks
5. Click "New Webhook", then click on the webhook you just created and change the name and profile picture to whatever you want
6. Click "Copy Webhook URL" and in the Arduino code, replace the channel id and token as specified with the comments in the code
7. Set your delay at the top of the code (This example has a 60-second delay between door being opened/closed and message being sent, so if someone's just passing by, it won't send the update)
8. Upload, plug in the arduino, and enjoy

Follow for more tips
