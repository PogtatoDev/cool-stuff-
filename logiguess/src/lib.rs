use colored::{Color, Colorize};

pub enum LogLevel {
    Info,
    Warning,
    Error,
    Fatal
}

impl LogLevel {
    pub fn prefix(&self) -> &str {
        match self {
            LogLevel::Info => "[INFO]",
            LogLevel::Warning => "[WARNING]",
            LogLevel::Error => "[ERROR]",
            LogLevel::Fatal => "[FATAL]"
        }
    }

    pub fn color(&self) -> Color {
        match self {
            LogLevel::Info => Color::Green,
            LogLevel::Warning => Color::Yellow,
            LogLevel::Error => Color::Red,
            LogLevel::Fatal => Color::BrightRed
        }
    }
}

pub fn log(level: LogLevel, text: &str) {
    println!("{}: {}", level.prefix(), text);
}

pub fn log_color(level: LogLevel, text: &str) {
    println!("{}: {}", level.prefix().color(level.color()), text);
}


