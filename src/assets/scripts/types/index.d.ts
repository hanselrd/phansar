interface logger {
    trace: (message: string) => void;
    debug: (message: string) => void;
    info: (message: string) => void;
    warning: (message: string) => void;
    error: (message: string) => void;
    critical: (message: string) => void;
}

interface logger_constructor {
    new1: (this: void, name: string, path: string, size: number, count: number) => logger;
}

declare const logger: logger_constructor;

interface material {
    ambient: [number, number, number];
    diffuse: [number, number, number];
    specular: [number, number, number];
    shininess: number;
    x: number;
    y: number;
    number: number;
    func: () => void;
}

interface material_constructor {
    new1: (this: void) => material;
}

declare const material: material_constructor;

declare enum color {
    white,
    black,
    red,
    blue,
    green,
    yellow,
    cyan,
    magenta,
    pink,
}

declare enum permissions {
    read,
    write,
    execute,
    read_write,
    read_execute,
    write_execute,
    read_write_execute,
}
