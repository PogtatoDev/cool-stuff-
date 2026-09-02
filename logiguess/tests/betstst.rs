use logiguess::*;

#[test]
fn run_tests_iguessbrowahtsnkjdhjsdjh() {
    log_color(LogLevel::Info, "hi guys!");
    log_color(LogLevel::Warning, "oops guys!");
    log_color(LogLevel::Error, "noooo guys!");
    log_color(LogLevel::Fatal, "FUCK GUYS!");
    log_color(LogLevel::Info, &format!("woah!, {}", 67 + 2));
}
