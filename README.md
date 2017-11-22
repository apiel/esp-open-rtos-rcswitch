This is an example to use RCswitch, a library originally build for arduino. This library allow you to receive and transmit rf 433 signal.

See their git repo: https://github.com/sui77/rc-switch

For this example you need to connect a rf receiver on the GPIO 12, in my case pin 6 with Wemos mini. Be careful some receiver accept 5V but I didn't manage to make it work, even if with the Arduino firmware it work. It seem to be an issue with the handle interupt. If someone manage to fix this issue, I would be really happy. Therefor, you should always use 3.3V pin to power up your rf receiver.
