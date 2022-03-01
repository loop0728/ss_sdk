mkdir /var/tmp
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib:/config/lib:/customer/lib:/lib
cd /customer
chmod 777 zkgui
./zkgui &
