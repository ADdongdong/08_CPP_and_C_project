#include "log.h"
#include <map>
#include <functional>
#include <iostream>


namespace adong{


const char* LogLevel::ToString(LogLevel::Level level) {
    switch (level) {
#define XX(name) \
    case LogLevel::name: \
        return #name; \
        break;

    XX(DEBUG);
    XX(INFO);
    XX(WARN);
    XX(ERROR);
    XX(FATAL);
#undef XX
    default:
        return "UNKNOW";
    }
    return "UNKNOW";
}

class MessageFormatItem : public LogFormatter::FormatItem {
// 虚类
public:
    MessageFormatItem(const std::string& str = ""){}
    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override{
        os << event->getContent();
    }
};

class LevelFOrmatItem : public LogFormatter::FormatItem {
public:
    LevelFOrmatItem(const std::string& str = ""){}
    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override{
        os << LogLevel::ToString(level);
    }
};

class ElapseFormatItem : public LogFormatter::FormatItem {
public:
    ElapseFormatItem(const std::string& str = ""){}
    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override{
        os << event->getElapse();
    }
};

class NameFormatItem : public LogFormatter::FormatItem {
public:
    NameFormatItem(const std::string& str = ""){}
    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override{
        os << event->getName();
    }
};


class ThreadIdFormatItem : public LogFormatter::FormatItem {
public:
    ThreadIdFormatItem(const std::string& str = ""){}
    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override{
        os << event->getThreadId();
    }
};

class FiberIdFormatItem : public LogFormatter::FormatItem {
public:
    FiberIdFormatItem(const std::string& str = ""){}
    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override{
        os << event->getFiberID();
    }
};

class DateTimeFormatItem : public LogFormatter::FormatItem {
public:
    DateTimeFormatItem(const std::string& format = "%Y:%m:%d %H:%M:%S")
        :m_format(format){}
    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override{
        os << event->getFiberID();
    }
private:
    std::string m_format;
};

// 文件名
class FilenameFormatItem : public LogFormatter::FormatItem {
public:
    FilenameFormatItem(const std::string& str = ""){}
    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override{
        os << event->getFiberID();
    }
};

class StringFormatItem : public LogFormatter::FormatItem {
public:
    StringFormatItem(const std::string& str)
        :m_string(str) {}
    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override{
        os << m_string;
    }
private:
    std::string m_string;
};

// 行号
class LineFormatItem : public LogFormatter::FormatItem {
public:
    LineFormatItem(const std::string& str = ""){}
    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override{
        os << event->getFiberID();
    }
};

// 换行
class NewLineFormatItem : public LogFormatter::FormatItem {
public:
    NewLineFormatItem(const std::string& str = ""){}
    void format(std::ostream& os, Logger::ptr logger, LogLevel::Level level, LogEvent::ptr event) override{
        os << std::endl;
    }
};

Logger::Logger(const std::string& name):m_name(name){
    m_formatter.reset(new LogFormatter("%t [%p] %f:%l %m %n"));

}

void Logger::addAppender(LogAppender::ptr appender) {
    m_appenders.push_back(appender);
}

void Logger::delAppender(LogAppender::ptr appender) {
    for (auto it = m_appenders.begin();
            it != m_appenders.end(); ++it) {
        if (*it == appender) {
            m_appenders.erase(it);
            break;
        }
    }


}

void Logger::log(LogLevel::Level level, const LogEvent::ptr event){
    if (level >= m_level) {
        auto self = shared_from_this();
        for (auto& i : m_appenders) {
            i->log(self, level, event);
        }
    }

}

void Logger::debug(LogEvent::ptr event) {
    log(LogLevel::DEBUG, event);
}

void Logger::info(LogEvent::ptr event) {
    log(LogLevel::INFO, event);
}

void Logger::warn(LogEvent::ptr event) {
    log(LogLevel::WARN, event);
}

void Logger::error(LogEvent::ptr event) {
    log(LogLevel::ERROR, event);

}

void Logger::fatal(LogEvent::ptr event) {
    log(LogLevel::FATAL, event);
}

FileLogAppender::FileLogAppender(const std::string& filename)
    :m_filename(filename) {

}

void FileLogAppender::log(std::shared_ptr<Logger> logger, LogLevel::Level level ,LogEvent::ptr event){
    if (level >= m_level) {
        m_filestream << m_formatter->format(logger , level ,event);
    }
}

bool FileLogAppender::reopen() {
    if (m_filestream) {
        m_filename.close();
    }
    m_filestream.open(m_filename);
    return !m_filestream;
}

void StdoutLogAppender::log(std::shared_ptr<Logger> logger, LogLevel::Level level,LogEvent::ptr event) {
    if (level >= m_level) {
        std::cout << m_formatter->format(logger, level, event);
    }
}

LogFormatter::LogFormatter(const std::string& pattern)
    :m_pattern(pattern){

}

// 日志输出的格式：%t %thread_id %m%n
std::string LogFormatter::format(std::ostream& os, std::shared_ptr<Logger> logger, LogLevel::Level level, LogEvent::ptr event) {
    std::stringstream ss;
    for(auto& i : m_items){
        i->format(ss, logger, level, event);
    }
    return ss.str();
}

//%xxx %xxx{xxx} %% 一共这3中格式，除了这3种格式，其他都是非法的
void LogFormatter::init() {
    // str, format, type
    std::vector<std::tuple<std::string, std::string, int>> vec;
    std::string nstr; //用str来表示当前的string是什么 
    size_t last_pos = 0;
    for (size_t i = 0; i < m_pattern.size(); ++i) {
        if (m_pattern[i] != '%') {
            nstr.append(1, m_pattern[i]);
            continue;
        }
        if ((i + 1) < m_pattern.size()){
            if (m_pattern[i + 1] == '%'){
                nstr.append(1, '%');
                continue;
            }
        }
        size_t n = i + 1;
        int fmt_status = 0;
        size_t fmt_begin = 0;

        std::string str;
        std::string fmt;

        while (n < m_pattern.size()) {
            if (isspace(m_pattern[n])) {
            // 检查下有没有空格符
                break;// 如果有，则中端了
            }
            if (fmt_status == 0) {
                if (m_pattern[n] == '{') {
                    str = m_pattern.substr(i + 1, n - i);
                    fmt_status = 1; // 解析格式
                    fmt_begin = n;
                    ++n;
                    continue;
                }
            }
            if (fmt_status == 1) {
                if (m_pattern[n] == '}') {
                    fmt = m_pattern.substr(fmt_begin+1, n - fmt_begin);
                    fmt_status = 2;
                    break;
                }
            }
        }

        if (fmt_status == 0) {
            if (!nstr.empty()){
                vec.push_back(std::make_tuple(nstr, std::string() ,0));
            }
            str = m_pattern.substr(i + 1, n - i - 1);
            vec.push_back(std::make_tuple(str, fmt, 1));
            i = n;
        } else if (fmt_status == 1) {
            std::cout << "pattern parse error:" << m_pattern << " - " << m_pattern.substr[i] << std::end;
            vec.push_back(std::make_tuple("<<pattern_error>>", fmt, 1));
        } else if (fmt_status == 2) {
            vec.push_back(std::make_tuple(str, fmt, 1));
            i = n;
        }
    }
    if (!nstr.empty()){
        vec.push_back(std::make_tuple(nstr, "" ,0));
    }
    // map的第二个目模板参数为一个可以被callable，可以是函数，lambda,函数对象，函数指针
    // 这里FormatItem::ptr指的是返回值，(const std::string) 指的是参数列表
    static std::map<std::string, std::function<FormatItem::ptr(const std::string)>> s_format_items = {
#define XX(str, C)\
        (#str, [](const std:;string& fmt) { return FormatItem::ptr(new C(fmt));})

        XX(m, MessageFormatItem),
        XX(p, LevelFOrmatItem),
        XX(r, ElapseFormatItem),
        XX(c, NameFormatItem),
        XX(t, ThreadIdFormatItem),
        XX(n, NewLineFormatItem),
        XX(d, DateTimeFormatItem),
        XX(f, FilenameFormatItem),
        XX(l, LineFormatItem),
#undef XX
    };

    for (auto& i : vec) {
        // get函数用于从元组中提取元素，2表示提取元组中第三个元素
        if (std::get<2>(i) == 0) {
            m_items.push_back(FormatItem::ptr(new StringFormatItem(std:;get<0>(i))));
        } else {
            auto it = s_format_items.find(std::get<0>(i));
            if (it == s_format_items.end()) {
                m_items.push_back(FormatItem::ptr(new StringFormatItem("<<error_format %" + std::get<0>(i) + ">>")));
            }else {
                m_items.push_back(it->second(std::get<1>(i)));
            }
        }
        std::cout << std::get<0>(i) << " - " << std::get<1>(i) << " - " << std::get<2>(1) << std::endl;
    }

    // %m -- 消息体
    // %p -- 日志level
    // %r -- 启动后的时间
    // %c -- 日志名称
    // %n -- 回车换行
    // %d -- 时间
    // %f -- 文件名称
    // %l -- 行号

}


const char* m_file = nullptr; // 文件名
int32_t m_line = 0;           // 行号
uint32_t m_elapse = 0;        // 程序启动到现在的毫秒数
uint32_t m_threadId = 0;      // 线程id
uint32_t m_fiberId = 0;       // 协程
uint64_t m_time = 0;          // 时间戳
std::string m_content;



};
