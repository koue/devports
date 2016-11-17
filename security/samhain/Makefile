# $FreeBSD$

PORTNAME=	samhain
PORTVERSION=	4.2.0
CATEGORIES=	security
MASTER_SITES=	http://la-samhna.de/archive/
DISTNAME=	samhain_signed-${PORTVERSION}

MAINTAINER=	koue@chaosophia.net
COMMENT=	The Samhain Intrusion Detection System

LICENSE=	GPLv2

OPTIONS_DEFINE=	KCHECK GPG MYSQL PGSQL XML_LOGS LIBWRAP PRELUDE
OPTIONS_DEFAULT=	XML_LOGS LIBWRAP
KCHECK_DESC=	Enable rogue KLD detection
GPG_DESC=	Enable GnuPG support
MYSQL_DESC=	Enable MySQL logging
PGSQL_DESC=	Enable PostgreSQL logging
XML_LOGS_DESC=	Enable XML-formatted logs
LIBWRAP_DESC=	Enable TCP wrapper support
PRELUDE_DESC=	Enable Prelude Framework support

SUB_FILES+=	pkg-install

WRKSRC=		${WRKDIR}/${PORTNAME}-${PORTVERSION}

GNU_CONFIGURE=	yes
CONFIGURE_ARGS=	--enable-login-watch \
		--localstatedir=/var \
		--enable-suidcheck \
		--with-logserver=true

USES=			shebangfix
SHEBANG_FILES=		scripts/samhainadmin.pl.in

.include <bsd.port.pre.mk>

.if ${ARCH} == "amd64"
CFLAGS+=	-fPIC
.endif

GPG_CONFIGURE_WITH=	gpg=${PREFIX}/bin/gpg
GPG_BUILD_DEPENDS=	gpg:${PORTSDIR}/security/gnupg

XML_LOGS_CONFIGURE_ENABLE=	xml-log

KCHECK_CONFIGURE_WITH=	kcheck

MYSQL_USES=		mysql

PGSQL_USES=		pgsql

PRELUDE_LIB_DEPENDS=	prelude:${PORTSDIR}/security/libprelude
PRELUDE_CONFIGURE_WITH=	prelude

LIBWRAP_CONFIGURE_WITH=	libwrap

.if defined(WITH_RUNAS_USER)
CONFIGURE_ARGS+=	--enable-identity=${WITH_RUNAS_USER}
.else
CONFIGURE_ARGS+=	--enable-identity=yule
.endif

.if defined(WITH_CLIENT)
CONFIGURE_ARGS+=	--enable-network=client \
			--with-data-file=REQ_FROM_SERVER/var/lib/samhain/data.samhain \
			--with-config-file=REQ_FROM_SERVER
PLIST_SUB+=		SAMHAIN="" SETPWD="" YULE="@comment "
EXTRA_PATCHES+=		${FILESDIR}/fixsamhainrc.patch
MAN5+=			samhainrc.5
MAN8+=			samhain.8
.elif defined(WITH_SERVER)
CONFIGURE_ARGS+=	--enable-network=server
SUB_LIST+=		WITH_YULE="yes"
PLIST_SUB+=		YULE="" SAMHAIN="@comment " SETPWD="@comment "
EXTRA_PATCHES+=		${FILESDIR}/fixyulerc.patch
MAN5+=			yulerc.5
MAN8+=			yule.8
.else
SUB_LIST+=		WITH_YULE=""
PLIST_SUB+=		SAMHAIN="" YULE="@comment " SETPWD="@comment "
EXTRA_PATCHES+=		${FILESDIR}/fixsamhainrc.patch
MAN5+=			samhainrc.5
MAN8+=			samhain.8
.endif

pre-everything::

.if !defined(WITH_CLIENT) && !defined(WITH_SERVER)
	@${ECHO_MSG}
	@${ECHO_MSG} "Building Samhain in standalone mode."
	@${ECHO_MSG} "If you wish to enable networked mode, please hit CTRL-C"
	@${ECHO_MSG} "now, and build samhain from the samhain-client and"
	@${ECHO_MSG} "samhain-server ports."
	@${ECHO_MSG}
.endif

.if defined(WITH_CLIENT) && defined(WITH_SERVER)
IGNORE=		can't build client and server at once
.endif

.if ${PORT_OPTIONS:MKCHECK}
	@${ECHO_MSG}
	@${ECHO_MSG} "Building with kernel checking requires reading /dev/kmem"
	@${ECHO_MSG} "and /dev/mem. If you're not building as root, please hit"
	@${ECHO_MSG} "Control-C and restart the build as root."
	@${ECHO_MSG}
.endif

.if ${PORT_OPTIONS:MMYSQL} && ! ${PORT_OPTIONS:MXML_LOGS}
IGNORE=		XML logging is required to log to MySQL
.endif

.if ${PORT_OPTIONS:MPGSQL} && ! ${PORT_OPTIONS:MXML_LOGS}
IGNORE=		XML logging is required to log to Postgres
.endif

post-extract:
	@${TAR} -C ${WRKDIR} -xzf ${WRKSRC}.tar.gz
	@${RM} ${WRKSRC}.tar.gz ${WRKSRC}.tar.gz.asc

pre-install:
	@PREFIX=${PREFIX} ${SH} ${PKGINSTALL} ${PKGNAME} PRE-INSTALL

post-install:
.if !defined(WITH_SERVER)
	@${CP} ${WRKSRC}/init/samhain.startFreeBSD ${STAGEDIR}${PREFIX}/etc/rc.d/samhain.sh
	@${CP} ${WRKSRC}/samhainrc ${STAGEDIR}${PREFIX}/etc/samhainrc.sample
	@${CHGRP} wheel ${STAGEDIR}${PREFIX}/etc/samhainrc.sample
.else
	@${CP} ${WRKSRC}/init/samhain.startFreeBSD ${STAGEDIR}${PREFIX}/etc/rc.d/yule.sh
	@${CP} ${WRKSRC}/yulerc ${STAGEDIR}${PREFIX}/etc/yulerc.sample
.endif
.if ${PORT_OPTIONS:MDOCS}
	${MKDIR} ${STAGEDIR}${DOCSDIR}
	${INSTALL_MAN} ${WRKSRC}/docs/MANUAL-2_4.pdf ${STAGEDIR}${DOCSDIR}
	${INSTALL_MAN} ${WRKSRC}/docs/HOWTO-client+server.html ${STAGEDIR}${DOCSDIR}
	${INSTALL_MAN} ${WRKSRC}/docs/HOWTO-client+server-troubleshooting.html ${STAGEDIR}${DOCSDIR}
	${INSTALL_MAN} ${WRKSRC}/docs/HOWTO-samhain+GnuPG.html ${STAGEDIR}${DOCSDIR}
	${INSTALL_MAN} ${WRKSRC}/docs/HOWTO-write-modules.html ${STAGEDIR}${DOCSDIR}
	${INSTALL_MAN} ${WRKSRC}/docs/FAQ.html ${STAGEDIR}${DOCSDIR}
	${INSTALL_MAN} ${WRKSRC}/docs/README.UPGRADE ${STAGEDIR}${DOCSDIR}
	${INSTALL_MAN} ${WRKSRC}/docs/README ${STAGEDIR}${DOCSDIR}
	${INSTALL_MAN} ${WRKSRC}/docs/BUGS ${STAGEDIR}${DOCSDIR}
	${INSTALL_MAN} ${WRKSRC}/docs/sh_mounts.txt ${STAGEDIR}${DOCSDIR}
	${INSTALL_MAN} ${WRKSRC}/docs/sh_userfiles.txt ${STAGEDIR}${DOCSDIR}
.endif

post-stage:
.if !defined(WITH_SERVER)
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/sbin/samhain
.endif
.if defined(WITH_CLIENT)
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/sbin/samhain_setpwd
.endif
.if defined(WITH_SERVER)
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/sbin/yule
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/sbin/yulectl
	${STRIP_CMD} ${STAGEDIR}${PREFIX}/sbin/yule_setpwd
.endif

	@${CAT} ${PKGMESSAGE}
.include <bsd.port.post.mk>
