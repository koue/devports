# $FreeBSD$

PORTNAME=	httpd
PORTVERSION=	5.8.20151023
CATEGORIES=	www

MAINTAINER=	koue@chaosophia.net
COMMENT=	OpenBSD http server

LICENSE=	BSD3CLAUSE

DISTFILES=	${PORTNAME}-${PORTVERSION}.tar.gz

WRKSRC=		${WRKDIR}/${PORTNAME}-${PORTVERSION}/src/usr.sbin/${PORTNAME}

USE_GITHUB=	yes
GH_ACCOUNT=	koue
GH_PROJECT=	httpd
GH_TAGNAME=	${PORTVERSION}

USE_OPENSSL=	yes
USE_RC_SUBR=	obhttpd

WITH_OPENSSL_PORT=yes
OPENSSL_PORT=	security/libressl

CFLAGS+=	-Wall

MAKE_ARGS+=	BINDIR=${PREFIX}/sbin MANDIR=${PREFIX}/man/man

USERS=		www
GROUPS=		www

PLIST_FILES=	sbin/obhttpd \
		man/man5/httpd.conf.5.gz \
		man/man7/patterns.7.gz \
		man/man8/obhttpd.8.gz

post-patch:
	${REINPLACE_CMD} -e "s|httpd$$|obhttpd|g" ${WRKSRC}/Makefile
	${REINPLACE_CMD} -e 's|httpd.8|obhttpd.8|g' ${WRKSRC}/Makefile
	${MV} ${WRKSRC}/httpd.8 ${WRKSRC}/obhttpd.8
	${REINPLACE_CMD} -e 's|/etc/httpd.conf|${PREFIX}/etc/obhttpd.conf|g' \
		${WRKSRC}/httpd.h

.include <bsd.port.mk>
