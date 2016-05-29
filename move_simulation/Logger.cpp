#include "stdafx.h"
#include "Logger.h"


Logger::Logger()
	: m_level(Info)
	, m_active_level(m_level)
	, m_out(nullptr)
	, m_owner(false)
{
}

void Logger::init(LogLevel level, std::ostream* stream, bool owner)
{
	m_level = level;

	if (m_out != nullptr && m_owner)
		delete m_out;
	m_out = stream;
	
	m_owner = owner;
}

Logger& Logger::operator<<(LogLevel const& level)
{
	m_active_level = level;
	return *this;
}

Logger& Logger::operator<<(std::ostream& (*pf)(std::ostream&))
{	
	if (m_out)
		(*m_out) << pf;
	return *this;
}

Logger::~Logger()
{
	if (m_owner)
		delete m_out;
}

Logger& logger()
{
	static Logger s_logger;
	return s_logger;
}
