mkdir /var/tmp
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib:/customer/lib:/lib:/config/lib
cd /customer
chmod 777 prog_p3_fb
chmod 777 prog_p3_gpio
chmod 777 prog_barcodeYuyan
./prog_barcodeYuyan &
