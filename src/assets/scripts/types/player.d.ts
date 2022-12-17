interface player {
  shoot: () => boolean;
  boost: () => boolean;
  brake: () => boolean;
  hp: number;
  bullets: number;
}

interface player_constructor {
  new: (this: void, bullets: number) => player;
  new2: (this: void, bullets: number) => player;
}

declare const player: player_constructor;
