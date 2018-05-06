/** @file */
#ifndef CONNECTION_H
#define CONNECTION_H

/**
 * Used to describe a connection associated the session's connection to the OpenTok messaging server.  * <p>
 */

#include "config.h"

OTC_BEGIN_DECL

typedef struct otc_connection otc_connection;

/**
 * gets a unique identifier for this connection.
 *
 * @param connection the stream being queried
 * @return A unique identifier for this connection.
 */
OTC_DECL(const char *) otc_connection_get_id(const otc_connection *connection);

/**
 * gets the creation time of the connection.
 *
 * @param connection the connection being queried
 * @return the creation time of the connection.
 */
OTC_DECL(otc_time_t) otc_connection_get_creation_time(const otc_connection *connection);

/**
 * gets the data associated with a connection.
 *
 * @param connection the connection being queried
 * @return the data associated with the connection.
 */
OTC_DECL(const char *) otc_connection_get_data(const otc_connection *connection);

/**
 * gets the session id associated with the connection.
 *
 * @param connection the connection being queried
 * @return the session id associated with the connection.
 */
OTC_DECL(const char *) otc_connection_get_session_id(const otc_connection *connection);

/**
 * Make a copy of this object. In session callbacks where a stream is sent by parameters, you need to copy the connection
 * if you plan to keep the instance longer than the life of the callback.
 *
 * @param connection The connection to be copied
 * @return the copied connection
 */
OTC_DECL(otc_connection *) otc_connection_copy(const otc_connection *connection);

/**
 * Releases this object, including all hardware resources bound to it.
 *
 * @param connection the connection which will me affected
 * @return an error in the event of an error otherwise OTC_SUCCESS
 */
OTC_DECL(otc_status_t) otc_connection_delete(otc_connection *connection);


OTC_END_DECL

#endif // CONNECTION_H
