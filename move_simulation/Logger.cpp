#include "stdafx.h"
#include "Logger.h"

namespace
{
	const char* level2string(const Logger::LogLevel level)
	{
		switch (level)
		{
			case Logger::Info: return "Info";
			case Logger::Warning: return "Warning";
			case Logger::Error: return "Error";
			default: return "Undefined";
		}
	}
}

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

Logger& Logger::operator<<(const LogLevel& level)
{
	m_active_level = level;

	if (m_out)
	{
		auto c_now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		*m_out << "[" << std::put_time(std::localtime(&c_now), "%F %T") << "] ";
		*m_out << level2string(level) << ": ";
	}

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
