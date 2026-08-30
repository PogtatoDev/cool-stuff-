use colored::{Color, Colorize};

pub enum LogLevel {
    Info,
    Warning,
    Error,
    Lethal
}

pub fn log(level: LogLevel, text: &str) {
    let prefix: &str;

    match level {
        LogLevel::Info => prefix = "[INFO]",
        LogLevel::Warning => prefix = "[WARNING]",
        LogLevel::Error => prefix = "[ERROR]",
        LogLevel::Lethal => prefix = "[LETHAL]"
    }

    println!("{}: {}", prefix, text);
}

pub fn log_color(level: LogLevel, text: &str) {
    let prefix: &str;
    let color: Color;

    match level {
        LogLevel::Info => { prefix = "[INFO]"; color = Color::Green },
        LogLevel::Warning => { prefix = "[WARNING]"; color = Color::Yellow },
        LogLevel::Error => { prefix = "[ERROR]"; color = Color::Red },
        LogLevel::Lethal => { prefix = "[LETHAL]"; color = Color::BrightRed }
    }

    println!("{}: {}", prefix.color(color), text);
}


