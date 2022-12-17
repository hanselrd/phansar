// lua["p2"] = player(0);
declare const p2: player;

function main(...args: any[]) {
  const p1 = player.new(2);
  const p2shoots = p2.shoot();
  assert(!p2shoots);

  p1.hp = 545;
  print(p1.hp);
  assert(p1.hp === 545);

  const did_shoot_1 = p1.shoot();
  print(did_shoot_1);
  print(p1.bullets);
  const did_shoot_2 = p1.shoot();
  print(did_shoot_2);
  print(p1.bullets);
  const did_shoot_3 = p1.shoot();
  print(did_shoot_3);

  print(p1.bullets);

  p1.boost();

  p1.brake();
}

main();
