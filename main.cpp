#include <iostream>
#include <ctime>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

namespace logging = boost::log;
namespace keywords = boost::log::keywords;
namespace attrs = boost::log::attributes;

#define LOG_TRACE  BOOST_LOG_TRIVIAL(trace)
#define LOG_DEBUG BOOST_LOG_TRIVIAL(debug) 
#define LOG_INFO     BOOST_LOG_TRIVIAL(info) 
#define LOG_WARN    BOOST_LOG_TRIVIAL(warning) 
#define LOG_ERROR    BOOST_LOG_TRIVIAL(error) 
#define LOG_FATAL    BOOST_LOG_TRIVIAL(fatal)

std::string datetime()
{
    time_t rawtime;
    struct tm * timeinfo;
    char buffer[80];

    time (&rawtime);
    timeinfo = localtime(&rawtime);

    strftime(buffer,80,"%d-%m-%Y %H-%M-%S",timeinfo);
    return std::string(buffer);
}

void init_logging()
{
    logging::register_simple_formatter_factory<logging::trivial::severity_level, char>("Severity");

    logging::add_file_log(
        keywords::file_name = datetime() + "_log.txt",
        //keywords::format = "[%TimeStamp%] [%ThreadID%] [%Severity%] [%ProcessID%] [%LineID%] [%MyAttr%] [%CountDown%] %Message%"
        keywords::format = "[%Severity%] [%LineID%] %Message%"
    );

    logging::core::get()->set_filter
    (
        logging::trivial::severity >= logging::trivial::trace
    );

    logging::core::get()->add_global_attribute("MyAttr", attrs::constant<int>(42));
    logging::core::get()->add_global_attribute("CountDown", attrs::counter<int>(100, -1));

    logging::add_common_attributes();

    BOOST_LOG_TRIVIAL(fatal) << datetime();
}

int main(int, char*[])
{
    init_logging();

    LOG_TRACE << "This is a trace severity message";
    LOG_DEBUG << "This is a debug severity message";
    LOG_INFO << "This is an informational severity message";
    LOG_WARN << "This is a warning severity message";
    LOG_ERROR << "This is an error severity message";
    LOG_FATAL << "and this is a fatal severity message";

    std::cout << "Press any key to continue..";
    std::cin.get();
    return 0;
}

