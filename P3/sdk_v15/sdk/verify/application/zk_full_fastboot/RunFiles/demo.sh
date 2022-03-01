date 032912122020.12
mkdir /var/tmp
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib:/customer_app/lib:/customer_app/libsecurity:/lib:/config/lib:/config/wifi:/customer/lib
cd /customer_app
chmod 777 zkgui
./zkgui &
