
#include <signalzeug/ScopedConnection.h>


namespace signalzeug
{

ScopedConnection::ScopedConnection()
{
}

ScopedConnection::ScopedConnection(const Connection & connection)
:   m_connection(connection)
{
}

ScopedConnection::ScopedConnection(ScopedConnection && other)
:   m_connection(other.m_connection)
{
    other.m_connection = Connection();
}

ScopedConnection::~ScopedConnection()
{
	m_connection.disconnect();
}

ScopedConnection& ScopedConnection::operator=(const Connection & connection)
{
	m_connection.disconnect();
	m_connection = connection;

    return *this;
}

ScopedConnection& ScopedConnection::operator=(ScopedConnection && other)
{
    m_connection.disconnect();
    m_connection = other.m_connection;
    other.m_connection = Connection();

    return *this;
}

} // namespace signalzeug
