#[derive(Default, Clone, derive_builder::Builder)]
#[builder(setter(into))]
pub struct ApplicationConfig<'a> {
    #[builder(default = "\"Phansar\".into()")]
    pub name: String,
    #[builder(default = "(1, 0, 0, Some(\"alpha\".into()), None)")]
    pub version: (u64, u64, u64, Option<String>, Option<String>),
    #[builder(default = "\"Phansar developer(s)\".into()")]
    pub author: String,
    #[builder(default = "\"Phansar\".into()")]
    pub about: String,
    #[builder(default)]
    pub args: Vec<clap::Arg<'a, 'a>>,
    // #[builder(default)]
    // pub subcommands: Vec<clap::App<'a, 'a>>,
}

pub struct Application<'a> {
    pub config: ApplicationConfig<'a>,
    pub matches: clap::ArgMatches<'a>,
    pub runtime: tokio::runtime::Runtime,
}

impl<'a> Application<'a> {
    pub fn new(config: ApplicationConfig<'a>) -> Self {
        let matches = clap::App::new(config.name.clone())
            .version(&*format!(
                "{}.{}.{}{}{}",
                config.version.0,
                config.version.1,
                config.version.2,
                match config.version.3 {
                    | Some(ref pre_release) => format!("-{}", pre_release),
                    | _ => "".into(),
                },
                match config.version.4 {
                    | Some(ref build_metadata) => format!("+{}", build_metadata),
                    | _ => "".into(),
                }
            ))
            .args(&config.args)
            .arg(
                clap::Arg::with_name("log-level")
                    .short("l")
                    .long("log-level")
                    .value_name("LOG_LEVEL")
                    .possible_values(&["trace", "debug", "info", "warn", "error"])
                    .default_value(if cfg!(debug_assertions) {
                        "trace"
                    } else {
                        "info"
                    }),
            )
            .arg(
                clap::Arg::with_name("log-file")
                    .short("L")
                    .long("log-file")
                    .value_name("LOG_FILE")
                    .default_value("phansar.log"),
            )
            .arg(
                clap::Arg::with_name("host")
                    .short("H")
                    .long("host")
                    .value_name("HOST")
                    .default_value("0.0.0.0"),
            )
            .arg(
                clap::Arg::with_name("port")
                    .short("p")
                    .long("port")
                    .value_name("PORT")
                    .default_value("7000"),
            )
            .arg(
                clap::Arg::with_name("jobs")
                    .short("j")
                    .long("jobs")
                    .value_name("JOBS")
                    .default_value("0"),
            )
            .get_matches();

        env_logger::Builder::from_env(env_logger::Env::default().default_filter_or(
            if let Some(log_level) = matches.value_of("log-level") {
                if cfg!(debug_assertions) {
                    log_level.into()
                } else {
                    format!("phansar={}", log_level)
                }
            } else {
                if cfg!(debug_assertions) {
                    "trace".into()
                } else {
                    "phansar=info".into()
                }
            },
        ))
        .init();

        let runtime = if let Some(jobs) = matches.value_of("jobs") {
            let jobs = jobs.parse::<usize>().unwrap();

            if jobs == 0 {
                tokio::runtime::Builder::new_current_thread()
                    .enable_all()
                    .build()
                    .unwrap()
            } else {
                tokio::runtime::Builder::new_multi_thread()
                    .worker_threads(jobs)
                    .enable_all()
                    .build()
                    .unwrap()
            }
        } else {
            tokio::runtime::Builder::new_multi_thread()
                .enable_all()
                .build()
                .unwrap()
        };

        Self {
            config,
            matches,
            runtime,
        }
    }
}
