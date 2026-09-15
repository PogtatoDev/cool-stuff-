function main() {
    let sink = 10;
    for (let i = 0; i < 1e10; i += 1) {
        sink = Math.cos(sink);
    }

    console.log(sink);
}

main()