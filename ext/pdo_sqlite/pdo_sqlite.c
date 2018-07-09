/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2018 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author: Wez Furlong <wez@php.net>                                    |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "pdo/php_pdo.h"
#include "pdo/php_pdo_driver.h"
#include "php_pdo_sqlite.h"
#include "php_pdo_sqlite_int.h"
#include "zend_exceptions.h"

ZEND_DECLARE_MODULE_GLOBALS(pdo_sqlite)

static PHP_GINIT_FUNCTION(pdo_sqlite);

/* {{{ pdo_sqlite_functions[] */
static const zend_function_entry pdo_sqlite_functions[] = {
	PHP_FE_END
};
/* }}} */

/* {{{ pdo_sqlite_deps
 */
static const zend_module_dep pdo_sqlite_deps[] = {
	ZEND_MOD_REQUIRED("pdo")
	ZEND_MOD_END
};
/* }}} */

/* {{{ pdo_sqlite_module_entry
 */
zend_module_entry pdo_sqlite_module_entry = {
	STANDARD_MODULE_HEADER_EX, NULL,
	pdo_sqlite_deps,
	"pdo_sqlite",
	pdo_sqlite_functions,
	PHP_MINIT(pdo_sqlite),
	PHP_MSHUTDOWN(pdo_sqlite),
	NULL,
	NULL,
	PHP_MINFO(pdo_sqlite),
	PHP_PDO_SQLITE_VERSION,
	PHP_MODULE_GLOBALS(pdo_sqlite),
	PHP_GINIT(pdo_sqlite),
	NULL,
	NULL,
	STANDARD_MODULE_PROPERTIES_EX
};
/* }}} */

#if defined(COMPILE_DL_PDO_SQLITE) || defined(COMPILE_DL_PDO_SQLITE_EXTERNAL)
ZEND_GET_MODULE(pdo_sqlite)
#endif

/* {{{ PHP_INI
*/
PHP_INI_BEGIN()
	STD_PHP_INI_ENTRY("pdo_sqlite.extension_dir",  NULL, PHP_INI_SYSTEM, OnUpdateString, extension_dir, zend_pdo_sqlite_globals, pdo_sqlite_globals)
PHP_INI_END()
/* }}} */

/* {{{ PHP_MINIT_FUNCTION */
PHP_MINIT_FUNCTION(pdo_sqlite)
{
	REGISTER_INI_ENTRIES();

#ifdef SQLITE_DETERMINISTIC
	REGISTER_PDO_CLASS_CONST_LONG("SQLITE_DETERMINISTIC", (zend_long)SQLITE_DETERMINISTIC);
#endif

	REGISTER_PDO_CLASS_CONST_LONG("SQLITE_ATTR_OPEN_FLAGS", (zend_long)PDO_SQLITE_ATTR_OPEN_FLAGS);
	REGISTER_PDO_CLASS_CONST_LONG("SQLITE_OPEN_READONLY", (zend_long)SQLITE_OPEN_READONLY);
	REGISTER_PDO_CLASS_CONST_LONG("SQLITE_OPEN_READWRITE", (zend_long)SQLITE_OPEN_READWRITE);
	REGISTER_PDO_CLASS_CONST_LONG("SQLITE_OPEN_CREATE", (zend_long)SQLITE_OPEN_CREATE);

	return php_pdo_register_driver(&pdo_sqlite_driver);
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION */
PHP_MSHUTDOWN_FUNCTION(pdo_sqlite)
{
	php_pdo_unregister_driver(&pdo_sqlite_driver);
	UNREGISTER_INI_ENTRIES();
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(pdo_sqlite)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "PDO Driver for SQLite 3.x", "enabled");
	php_info_print_table_row(2, "SQLite Library", sqlite3_libversion());
	php_info_print_table_end();

	DISPLAY_INI_ENTRIES();
}
/* }}} */

/* {{{ PHP_GINIT_FUNCTION
*/
static PHP_GINIT_FUNCTION(pdo_sqlite)
{
#if defined(COMPILE_DL_PDO_SQLITE) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	memset(pdo_sqlite_globals, 0, sizeof(*pdo_sqlite_globals));
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
