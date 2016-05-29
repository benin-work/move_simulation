#pragma once

class Logger
{
public:
	enum LogLevel
	{
		Info = 0,
		Warning,
		Error
	};

public:
	Logger();
	~Logger();

	void init(LogLevel level, std::ostream* stream, bool owner = false);

	template <typename T>
	Logger& operator<<(T const& value);

	// Level information
	Logger& operator<<(LogLevel const& level);

	// Stream manipulators adoptation
	Logger& operator<<(std::ostream& (*pf)(std::ostream&));

private:
	LogLevel m_level;
	LogLevel m_active_level;
	std::ostream* m_out;
	bool m_owner;
};

template <typename T>
Logger& Logger::operator<<(T const & value)
{
	if (m_active_level < m_level )
		return *this;

	if (m_out)
		*m_out << value;
	
	return *this;
}


Logger& logger();
