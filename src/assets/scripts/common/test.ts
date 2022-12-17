const log = (...args: any[]): void => {
  console.log(...args);
};

const pi = 3.14159;
log(`pi = ${pi}`);

const myList = [1, 2, 3];
myList.push(4);
myList.pop();
myList.splice(1, 1);
for (let e of myList) {
  log(`myList[elem] = ${e}`);
}

switch (0 as number) {
  case 0:
    log("0");
    break;
  case 1:
    log("1");
    break;
}

class Empty {}

class Point {
  x: number = 0;
  y: number = 0;
}

const pt = new Point();
console.log(`${pt.x}, ${pt.y}`);

class Greeter {
  name: string;

  constructor() {
    this.name = "hello";
  }
}

const G = new Greeter();
console.log(G.name);
