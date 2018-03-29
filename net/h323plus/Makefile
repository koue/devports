# $FreeBSD$

PORTNAME=	h323plus
PORTVERSION=	1.26.8
CATEGORIES=	net multimedia
MASTER_SITES=	http://www.h323plus.org/source/download/
DISTNAME=	${PORTNAME}-v${PORTVERSION:S/./_/g}

MAINTAINER=	koue@chaosophia.net
COMMENT=	H323 Video Conferencing library

LICENSE=	MPL10 MPL11
LICENSE_COMB=	multi

LIB_DEPENDS=	libpt.so:devel/ptlib \
		libexpat.so:textproc/expat2

WRKSRC=		${WRKDIR}/${PORTNAME}

USES=		gmake ssl
USE_SDL+=	sdl
GNU_CONFIGURE=	yes
USE_LDCONFIG=	yes

MAKE_JOBS_UNSAFE=yes

post-install:
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/lib/libh323.so.1.26.8

.include <bsd.port.mk>
