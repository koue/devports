--- src/utils/meas_udp2db.c.orig	2015-10-12 07:37:35 UTC
+++ src/utils/meas_udp2db.c
@@ -37,6 +37,10 @@
 
 #include <openbsc/meas_feed.h>
 
+#ifdef __FreeBSD__
+#include <sys/socket.h>
+#endif
+
 #include "meas_db.h"
 
 static struct osmo_fd udp_ofd;
