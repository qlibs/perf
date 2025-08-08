/**
 * `perf`: C++23 Performance library
 * - https://github.com/qlibs/perf
 */
#ifndef PERF
#define PERF (0, 0, 0) /// (MAJOR, MINOR, PATCH) # https://semver.org

#ifndef PERF_GNU
#ifdef __GNUC__
  #define PERF_GNU 1
#else
  #define PERF_GNU 0
#endif
#endif

#if (not defined(PERF_LINUX)) or (defined(PERF_LINUX) and PERF_LINUX == 1)
#if __has_include(<cpuid.h>) and \
    __has_include(<unistd.h>) and \
    __has_include(<pthread.h>) and \
    __has_include(<sched.h>) and \
    __has_include(<sys/time.h>) and\
    __has_include(<sys/syscall.h>) and \
    __has_include(<sys/resource.h>) and \
    __has_include(<sys/ioctl.h>) and \
    __has_include(<sys/mman.h>) and \
    __has_include(<linux/perf_event.h>)
#include <cpuid.h>
#include <unistd.h>
#include <pthread.h>
#include <sched.h>
#include <sys/time.h>
#include <sys/syscall.h>
#include <sys/resource.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/perf_event.h>
#ifndef PERF_LINUX
  #define PERF_LINUX 1
#endif
#elif PERF_LINUX == 1
  #error "<linux*.h>"
#else
  #define PERF_LINUX 0
#endif
#endif

#if not defined(PERF_UEFI)
  #define PERF_UEFI 0
#endif

#if (not defined(PERF_LLVM)) or (defined(PERF_LLVM) and PERF_LLVM == 1)
#if __has_include(<llvm/TargetParser/Host.h>) and \
    __has_include(<llvm/TargetParser/Triple.h>) and \
    __has_include(<llvm/Support/TargetSelect.h>) and \
    __has_include(<llvm/Object/SymbolSize.h>) and \
    __has_include(<llvm/MC/MCDisassembler/MCDisassembler.h>) and \
    __has_include(<llvm/MC/MCInstPrinter.h>) and \
    __has_include(<llvm/MC/MCTargetOptions.h>) and \
    __has_include(<llvm/MC/TargetRegistry.h>) and \
    __has_include(<llvm/MC/MCContext.h>) and \
    __has_include(<llvm/MC/MCAsmInfo.h>) and \
    __has_include(<llvm/MC/MCInstrInfo.h>) and \
    __has_include(<llvm/MC/MCRegisterInfo.h>) and \
    __has_include(<llvm/MC/MCSubtargetInfo.h>) and \
    __has_include(<llvm/MCA/View.h>) and \
    __has_include(<llvm/MCA/Pipeline.h>) and \
    __has_include(<llvm/MCA/CodeEmitter.h>) and \
    __has_include(<llvm/MCA/Context.h>) and \
    __has_include(<llvm/MCA/InstrBuilder.h>) and \
    __has_include(<llvm/MCA/Stages/EntryStage.h>) and \
    __has_include(<llvm/MCA/Stages/InstructionTables.h>) and \
    __has_include(<llvm/DebugInfo/Symbolize/Symbolize.h>)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#pragma GCC diagnostic ignored "-Wunused-parameter"
#include <llvm/TargetParser/Host.h>
#include <llvm/TargetParser/Triple.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/Object/SymbolSize.h>
#include <llvm/MC/MCDisassembler/MCDisassembler.h>
#include <llvm/MC/MCInstPrinter.h>
#include <llvm/MC/MCTargetOptions.h>
#include <llvm/MC/MCContext.h>
#include <llvm/MC/MCAsmInfo.h>
#include <llvm/MC/MCInstrInfo.h>
#include <llvm/MC/MCRegisterInfo.h>
#include <llvm/MC/MCSubtargetInfo.h>
#include <llvm/MCA/View.h>
#include <llvm/MCA/Pipeline.h>
#include <llvm/MCA/CodeEmitter.h>
#include <llvm/MCA/Context.h>
#include <llvm/MCA/InstrBuilder.h>
#include <llvm/MCA/Stages/EntryStage.h>
#include <llvm/MCA/Stages/InstructionTables.h>
#include <llvm/DebugInfo/Symbolize/Symbolize.h>
#pragma GCC diagnostic pop
#ifndef PERF_LLVM
  #define PERF_LLVM 1
#endif
#elif PERF_LLVM == 1
  #error "<llvm*.h>"
#else
  #define PERF_LLVM 0
#endif
#endif

#if (not defined(PERF_INTEL)) or (defined(PERF_INTEL) and PERF_INTEL == 1)
#if __has_include(<intel-pt.h>)
#include <intel-pt.h>
#ifndef PERF_INTEL
  #define PERF_INTEL 1
#endif
#elif PERF_INTEL == 1
  #error "<intel*.h>"
#else
  #define PERF_INTEL 0
#endif
#endif

#ifndef PERF_IO
  #define PERF_IO 1
#endif

#ifndef PERF_EVENT
  #define PERF_EVENT 1
#endif

#define PERF_IMPL_VERSION(MAJOR, MINOR, PATCH) v##MAJOR##_##MINOR##_##PATCH
#define PERF_IMPL_EVAL(...) __VA_ARGS__

#include <cstdint>
#include <climits>
#include <cstring>

#include <bit>
#include <atomic>
#include <barrier>
#include <thread>
#include <chrono>
#include <random>
#include <utility>
#include <memory>
#include <type_traits>
#include <concepts>

#include <string>
#include <string_view>
#include <iostream>
#include <ostream>
#include <fstream>
#include <initializer_list>
#include <format>
#include <stdexcept>
#include <source_location>
#include <filesystem>

#include <array>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <span>
#include <unordered_map>
#include <optional>
#include <any>

#include <numeric>
#include <algorithm>

namespace perf::inline v1_0_0 {
namespace utility {
  /**
   * verifies whether condition is satisfied / throws if not
   * @code
   *  try {
   *    // ...
   *  } catch (const std::exception& e) {
   *    std::println("{}{}", e.what(), std::stacktrace::current());
   *  }
   * @endcode
   */
  inline constexpr auto verify =
    [](const std::same_as<bool> auto cond, const std::convertible_to<std::string_view> auto&... msgs) {
      if (not cond) [[unlikely]] {
        [&] [[gnu::cold]] { throw std::runtime_error{(msgs + ... + std::string())}; }();
      }
    };

  template<class...> struct type_list { };
  template<class...> extern constexpr auto type_id = []{};

  #if __has_feature(reflection) /// `reflection for C++26` # https://wg21.link/p2996
  template<class T>
  extern constexpr auto meta = ^^T;
  using info = decltype(^^::);
  template<info meta>
  using type_of = typename [: meta :];
  #else
  namespace detail {
    template<auto...> struct info { constexpr auto friend get(info); };
    template<class T, auto... Tags> struct meta {
      [[nodiscard]] constexpr auto friend get(info<Tags...>) {
        return std::type_identity<T>{};
      }
    };
  } // namespace detail

  template<class T>
  extern constexpr auto meta = (detail::meta<T, type_id<T>>(), type_id<T>);
  using info = std::remove_cvref_t<decltype(meta<void>)>;
  template<auto meta>
  using type_of = typename decltype(get(detail::info<meta>{}))::type;
  #endif // reflection

  template<class...> struct function_traits;
  template<class T> requires requires { &T::operator(); }
  struct function_traits<T>
    : function_traits<decltype(&T::operator())>
  { };
  template<class T> requires requires { &T::template operator()<>; }
  struct function_traits<T>
    : function_traits<decltype(&T::template operator()<>)>
  { };
  template<class R, class... Ts>
  struct function_traits<R (Ts...)> {
    using result_type = R;
    using args_type = type_list<Ts...>;
  };
  template<class R, class... Ts>
  struct function_traits<R (Ts...) noexcept> {
    using result_type = R;
    using args_type = type_list<Ts...>;
  };
  template<class R, class... Ts>
  struct function_traits<R (*)(Ts...)> {
    using result_type = R;
    using args_type = type_list<Ts...>;
  };
  template<class R, class... Ts>
  struct function_traits<R (*)(Ts...) noexcept> {
    using result_type = R;
    using args_type = type_list<Ts...>;
  };
  template<class R, class T, class... Ts>
  struct function_traits<R (T::*)(Ts...) const> {
    using result_type = R;
    using args_type = type_list<Ts...>;
  };
  template<class R, class T, class... Ts>
  struct function_traits<R (T::*)(Ts...) const noexcept> {
    using result_type = R;
    using args_type = type_list<Ts...>;
  };
  template<class R, class T, class... Ts>
  struct function_traits<R (T::*)(Ts...)> {
    using result_type = R;
    using args_type = type_list<Ts...>;
  };
  template<class R, class T, class... Ts>
  struct function_traits<R (T::*)(Ts...) noexcept> {
    using result_type = R;
    using args_type = type_list<Ts...>;
  };

  #if __cpp_lib_fixed_string /// `std::basic_fixed_string` - https://wg21.link/p3094
  template<std::size_t N>
  using fixed_string = std::basic_fixed_string<char, N>;
  #else
  template<class T, std::size_t N>
  struct basic_fixed_string {
    constexpr basic_fixed_string() = default;
    constexpr explicit(false) basic_fixed_string(const T (&str)[N]) { std::copy_n(str, N, this->str); }
    [[nodiscard]] constexpr auto data() const { return str; }
    [[nodiscard]] static constexpr auto size() { return N - 1u; }

    template<class TView>
    [[nodiscard]] constexpr operator TView() const noexcept requires requires { TView{data(), size()}; } {
      return TView{data(), size()};
    }

    T str[N]{}; /// null terminated
  };
  template<std::size_t N>
  using fixed_string = basic_fixed_string<char, N>;
  #endif // __cpp_lib_fixed_string

  template<auto V>
    requires std::is_class_v<decltype(V)> and requires { decltype(V)(V); }
  struct constant : decltype(V) {
    constexpr constant() : decltype(V)(V) { }
  };

  template<class T>
    requires requires { T{}; }
  struct strong_alias {
    constexpr strong_alias() = default;
    constexpr explicit(false) strong_alias(const T& value)
      : value{value}
    { }
    [[nodiscard]] constexpr operator auto() const {
      return value;
    }
    T value{};
  };

  /**
   * named type with compile-time name
   */
  template<utility::fixed_string Name, class T>
    requires (std::is_class_v<T> and not std::is_final_v<T>)
  struct fixed_named : T {
    using underlying_type = T;

    constexpr fixed_named() = default;
    constexpr explicit fixed_named(auto&&... ts)
      requires requires { T(std::forward<decltype(ts)>(ts)...); }
      : T(std::forward<decltype(ts)>(ts)...)
    { }

    [[nodiscard]] static constexpr decltype(auto) name() {
      static constexpr auto name = Name;
      return (name);
    }
  };

  template<utility::fixed_string Name, class T>
  [[nodiscard]] inline constexpr auto make_fixed_named(T&& t)
    -> fixed_named<Name, std::remove_cvref_t<T>> {
    return fixed_named<Name, std::remove_cvref_t<T>>{std::forward<T>(t)};
  }

  template<class... Ts>
  struct tuple : Ts... {
    template<class T>
    [[nodiscard]] constexpr decltype(auto) operator[](T)
      requires requires { static_cast<T&>(*this); } {
      return static_cast<T&>(*this);
    }

    template<class T>
    [[nodiscard]] constexpr decltype(auto) operator[](T) const
      requires requires { static_cast<const T&>(*this); } {
      return static_cast<const T&>(*this);
    }
  };

  template<std::size_t N>
  inline constexpr auto unroll = [](auto&& fn) {
    const auto invoke = [&]<std::size_t I> {
      if constexpr (requires { fn.template operator()<std::size_t{}>(); }) {
        fn.template operator()<I>();
      } else {
        fn();
      }
    };
    [&]<std::size_t... Ns>(std::index_sequence<Ns...>) {
      (invoke.template operator()<Ns>(), ...);
    }(std::make_index_sequence<N>{});
  };

  template<class... Ts> struct overload : Ts... { using Ts::operator()...; };
  template<class... Ts> overload(Ts...) -> overload<Ts...>;

  /**
   * scoped { .on_entry = ctor, .on_exit = dtor }
   */
  template<class TOnEntry = decltype([]{}), class TOnExit = decltype([]{})>
  struct scoped final {
    TOnEntry on_entry{};
    TOnExit on_exit{};

    struct _on_entry {
      constexpr explicit _on_entry(const auto& on_entry) {
        on_entry();
      }
    } _on_entry{on_entry};

    constexpr ~scoped() noexcept {
      on_exit();
    }
  };
} // namespace utility

namespace info {
  namespace cpu {
    inline constexpr auto name = [] -> std::string {
      std::array<char, 48u + 1u> name{};
      std::array<unsigned int, 4u> info{};
      std::size_t n{};
      for (auto i = 0u; i < name.size() - 1u; i += 16u) {
        __get_cpuid(0x80000002 + n++, &info[0], &info[1], &info[2], &info[3]);
        std::memcpy(name.data() + i, info.data(), sizeof(info));
      }
      /// ex. '12th Gen Intel(R) Core(TM) i7-12650H'
      const std::size_t size = std::distance(name.begin(), std::find(name.begin(), name.end(), 0)) - 1u;
      utility::verify(size < name.size());
      return {name.data(), size};
    };

    struct cpu_ver {
      std::uint16_t family{};
      std::uint8_t model{};
      std::uint8_t stepping{};
    };

    inline constexpr auto version = [] {
      unsigned int eax{}, ebx{}, ecx{}, edx{};
      __get_cpuid(1u, &eax, &ebx, &ecx, &edx);

      const auto family = (eax >> 8u) & 0xF;
      const auto extended_family = (eax >> 20) & 0xFF;
      const auto model = (eax >> 4u) & 0xF;
      const auto extended_model = (eax >> 16u) & 0xF;

      return cpu_ver{
        .family = std::uint16_t(family == 0xF ? family + extended_family : family),
        .model = std::uint8_t(family == 0x6 or family == 0xF ? model + (extended_model << 4u) : model),
        .stepping = std::uint8_t(eax & 0xF),
      };
    };
  } // namespace cpu

  namespace sys {
    inline constexpr auto page_size = [] {
      return sysconf(_SC_PAGESIZE); // ex. '4096' [kb]
    };

    /**
     * loads hw info form the given path and parse it accordingly to the format
     */
    template<utility::fixed_string Fmt, class T = std::size_t>
    inline constexpr auto hw = [](const std::convertible_to<std::string_view> auto& path) {
      static constexpr auto size = [] {
        const auto view = std::string_view(Fmt);
        return 1u + std::count(view.begin(), view.end(), ',');
      }();

      std::ifstream file{path};
      if (not file.good()) {
        return std::optional<std::array<T, size>>();
      }
      std::string line{};
      std::getline(file, line);
      std::array<T, size> fields{};
      [&]<std::size_t... Ns>(std::index_sequence<Ns...>) {
        utility::verify(std::sscanf(line.c_str(), std::string(Fmt).c_str(), &fields[Ns]...) == size);
      }(std::make_index_sequence<size>{});

      return std::optional{fields};
    };
  } // namespace sys
} // namespace info

namespace core {
  namespace code {
    #if PERF_GNU == 1
    /**
     * gnu version of `[[clang::code_align(alignment)]]`
     */
    template<std::align_val_t Alignment>
      requires (std::has_single_bit(std::size_t(Alignment)))
    inline constexpr auto align = [] {
      asm volatile(".align %c0" : : "i"(Alignment));
    };

    /**
     * global compile-time code label # ld: `__start_labels`, `__stop_labels`
     * - local:  `LABEL: -> &&LABEL` # gnu extension
     * - global: `perf::code::label<"LABEL">() -> perf::code::labels["LABEL"]`
     */
    template<auto Label>
    inline constexpr auto label = [] {
      asm volatile goto(
        ".pushsection labels, \"aw\" \n"
        ".quad %c0, %l[L]\n" /// note: `.quad %c0, 0b` can be reordered
        ".popsection \n"
        : : "i"(Label) : "memory" : L
      ); L:;
    };

    /**
     * global compile-time code labels # see `perf::code::label`
     */
    extern "C" std::pair<std::uint64_t, std::uint64_t> __start_labels [[gnu::section("labels")]] [[gnu::weak]];
    extern "C" std::pair<std::uint64_t, std::uint64_t> __stop_labels [[gnu::section("labels")]] [[gnu::weak]];
    inline const struct labels : std::unordered_map<std::uint64_t, std::uint64_t> {
      using std::unordered_map<std::uint64_t, std::uint64_t>::unordered_map;
      [[nodiscard]] constexpr decltype(auto) operator[](const auto key) const
        requires requires { std::uint64_t(key); } {
          utility::verify(contains(std::uint64_t(key)));
        return at(std::uint64_t(key));
      }
    } labels{&__start_labels, &__stop_labels};
    #endif // PERF_GNU
  } // namespace code

  namespace compiler {
    /**
     * prevents elision of given value
     */
    inline constexpr auto prevent_elision = [](auto&& t) -> decltype(auto) {
      if constexpr (std::is_pointer_v<std::remove_cvref_t<decltype(t)>>) {
        asm volatile("" :: "g"(t) : "memory");
      } else {
        #if defined(__clang__)
        asm volatile("" :: "r,m"(t) : "memory");
        #else
        asm volatile("" :: "m,r"(t) : "memory");
        #endif
      }
      return (t);
    };
  } // namespace compiler
} // namespace core

namespace data {
  // unpredictable;
} // namespace data

namespace metric {
  // median
  // mean

inline namespace dsl {
  // operator/;
  // operator*;
  // operator+;
  // operator-;
} // namespace dsl
} // namespace metric

template<class... TEvents>
    requires (requires { TEvents::name(); typename TEvents::value_type; } and ...)
class profiler final {
  static constexpr auto read_format =
    PERF_FORMAT_ID                      /// event.id
  | PERF_FORMAT_GROUP                   /// group counters
  | PERF_FORMAT_TOTAL_TIME_ENABLED      /// multiplexing correction [optional]
  | PERF_FORMAT_TOTAL_TIME_RUNNING      /// multiplexing correction [optional]
  ;

  static constexpr auto mem_read_format =
    PERF_FORMAT_ID                    /// event.id
  | PERF_FORMAT_GROUP                 /// group counters
  ;

  static constexpr auto sample_type =
    PERF_SAMPLE_IP                      /// instruction pointer
  | PERF_SAMPLE_READ                    /// events
  ;

  static constexpr auto mem_sample_type =
    PERF_SAMPLE_IP                    /// instruction pointer
  | PERF_SAMPLE_ADDR                  /// address
  | PERF_SAMPLE_DATA_SRC              /// data source
  ;

  struct data final {
    std::uint64_t value{};
    std::uint64_t id{};
  };

  struct stat final {
    std::uint64_t size{};               /// events.size
    std::uint64_t total_time_enabled{}; /// multiplexing correction [optional]
    std::uint64_t total_time_running{}; /// multiplexing correction [optional]
    data values[(std::string_view(TEvents::name()).starts_with("stat.") + ... + 0u)]{};     /// `verify(size == sizeof...(TEvents))`
  };

  struct record final {
    std::uint64_t ip{};                 /// instruction pointer
    std::uint64_t size{};               /// events.size
    std::uint64_t total_time_enabled{}; /// multiplexing correction [optional]
    std::uint64_t total_time_running{}; /// multiplexing correction [optional]
    data values[(std::string_view(TEvents::name()).starts_with("record.") + ... + 0u)]{};     /// `verify(size == sizeof...(TEvents))`
  };

  struct mem final {
    std::uint64_t ip{};                 /// instruction pointer
    std::uint64_t dst{};                /// address
    std::uint64_t src{};                /// data source
  };

 public:
  struct target {
    struct vendor {
      std::string name = info::cpu::name();
      std::uint16_t family = info::cpu::version().family;
      std::uint8_t model = info::cpu::version().model;
      std::uint8_t stepping = info::cpu::version().stepping;
    } vendor{};

    enum mode {
      user        = 0b00001,
      kernel      = 0b00010,
      hypervisor  = 0b00100,
      idle        = 0b01000,
      guest       = 0b10000,
    } mode = mode::user;

    enum skid {             /// precise_ip
      arbitrary       = 0,  /// - can have arbitrary skid
      constant        = 1,  /// - must have constant skid
      requested_zero  = 2,  /// - requested to have 0 skid
      zero            = 3,  /// - must have 0 skid
    } skid = skid::zero;

    struct period { std::int32_t value{}; };
    struct frequency { std::int32_t value{}; };
    struct interval {
      constexpr interval(const frequency& f) : value{f.value} { }
      constexpr interval(const period& p) : value{-p.value} { }
      [[nodiscard]] constexpr operator auto() const {
        return value;
      }
     private:
      std::int32_t value{};
    } interval = period{1000};

    std::optional<std::int32_t> pid{};  /// pid of the process {not_set: current process, N: process<N>}
    std::optional<std::int32_t> cpu{};  /// cpu of the process {not_set: any_cpu, N: cpu<N>}

    std::size_t buffer_size = 512u * info::sys::page_size() + 1u; /// the first page is not used
    std::size_t aux_size = 2048u * info::sys::page_size(); /// intel_pt instructions are stored under aux buffer in compressed format
  };

  constexpr explicit profiler(const TEvents&... events)
      : profiler{{}, events...}
  { }

  constexpr explicit profiler(const target& target, const TEvents&... events)
      : target_{target}, events_{events...} {
    const auto pid = target_.pid ? *target_.pid : 0;
    const auto cpu = target_.cpu ? *target_.cpu : -1;

    ([&]<class TEvent>(const TEvent& event) {
      if constexpr (requires { event.config[0u]; event.type; } and std::string_view(TEvent::name()).starts_with("stat.")) {
        perf_event_attr attr{};
        attr.type = event.type;
        attr.size = sizeof(perf_event_attr);
        attr.config = event.config[0u];
        attr.read_format = read_format;
        attr.disabled = fd1_ == -1;
        attr.exclude_user = not (target_.mode & target::mode::user);
        attr.exclude_kernel = not (target_.mode & target::mode::kernel);
        attr.exclude_hv = not (target_.mode & target::mode::hypervisor);
        attr.exclude_idle = not (target_.mode & target::mode::idle);
        attr.exclude_guest = not (target_.mode & target::mode::guest);
        attr.config1 = event.config[1u];
        attr.config2 = event.config[2u];

        const auto fd = syscall(__NR_perf_event_open, &attr, pid, cpu, fd1_, 0);
        utility::verify(fd != -1, std::strerror(errno));
        ioctl(fd, PERF_EVENT_IOC_ID, &ids_[std::string_view(event.name())]);
        if (fd1_ == -1) {
          fd1_ = fd;
        }
      } else if constexpr (requires { event.config[0u]; event.type; } and std::string_view(TEvent::name()).starts_with("record.")) {
        perf_event_attr attr{};
        attr.type = event.type;
        attr.size = sizeof(perf_event_attr);
        attr.config = event.config[0u];
        attr.sample_type = sample_type;
        attr.read_format = read_format;
        attr.disabled = fd2_ == -1;
        attr.exclude_user = not (target_.mode & target::mode::user);
        attr.exclude_kernel = not (target_.mode & target::mode::kernel);
        attr.exclude_hv = not (target_.mode & target::mode::hypervisor);
        attr.exclude_idle = not (target_.mode & target::mode::idle);
        attr.exclude_guest = not (target_.mode & target::mode::guest);
        attr.wakeup_events = 1;
        attr.config1 = event.config[1];
        attr.config2 = event.config[2];

        if (target_.interval > 0) {
          attr.sample_freq = target_.interval;
        } else {
          attr.sample_period = std::abs(target_.interval);
        }

        auto fd = -1;
        for (auto pip = std::int32_t(target_.skid); pip >= 0; --pip) { /// aim for minimal skid
          attr.precise_ip = pip;
          fd = syscall(__NR_perf_event_open, &attr, pid, cpu, fd2_, 0);
          if (fd != -1) break;
        }
        utility::verify(fd != -1, std::strerror(errno));
        if (fd2_ == -1) {
          fd2_ = fd; /// leader
        }

        ioctl(fd, PERF_EVENT_IOC_ID, &ids_[std::string_view(event.name())]);
      } else if constexpr (std::string_view(TEvent::name()) == "trace.instructions") {
        perf_event_attr attr{};
        attr.type = static_cast<std::uint32_t>(event.value);
        attr.size = sizeof(perf_event_attr);
        attr.config =
            ([&] {
              if constexpr (std::string_view(TEvents::name()).starts_with("trace.cycles")) {
                return 1ull << events.value;
              } else {
                return 0ull;
              }
            }() | ... | 0u);
        attr.disabled = true;
        attr.exclude_user = not (target_.mode & target::mode::user);
        attr.exclude_kernel = not (target_.mode & target::mode::kernel);
        attr.exclude_hv = not (target_.mode & target::mode::hypervisor);
        attr.exclude_idle = not (target_.mode & target::mode::idle);
        attr.exclude_guest = not (target_.mode & target::mode::guest);

        fd_ = syscall(__NR_perf_event_open, &attr, pid, cpu, -1, 0);
        utility::verify(fd_ != -1);

        buffer_ = mmap(nullptr, target_.buffer_size, PROT_WRITE, MAP_SHARED, fd_, 0);
        utility::verify(buffer_ != MAP_FAILED);

        auto header = reinterpret_cast<perf_event_mmap_page*>(buffer_);
        header->aux_offset = header->data_offset + header->data_size;
        header->aux_size = target_.aux_size;

        aux_ = mmap(nullptr, header->aux_size, PROT_READ, MAP_SHARED, fd_, header->aux_offset);
        utility::verify(aux_ != MAP_FAILED);
      }
    }(events), ...);

    if (fd2_ != -1) {
      buffer2_ = mmap(nullptr, target_.buffer_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd2_, 0);
      utility::verify(buffer2_ != MAP_FAILED, std::strerror(errno));
    }
  }

  constexpr ~profiler() noexcept {
    if (fd_ != -1) { // trace
      utility::verify(not close(fd_));
      utility::verify(not munmap(aux_, target_.aux_size));
      utility::verify(not munmap(buffer_, target_.buffer_size));
    }
    if (fd1_ != -1) { // stat
      utility::verify(not close(fd1_));
    }
    if (fd2_ != -1) { // record
      utility::verify(not close(fd2_));
      utility::verify(not munmap(buffer2_, target_.buffer_size));
    }
  }

  template<auto StartLabel = +[]{}>
  constexpr auto start() noexcept {
    // TODO rdpmc for cycles instructions

    if (fd2_ != -1) { // record
      ioctl(fd2_, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
    }

    if (fd_ != -1) { // trace
      ioctl(fd_, PERF_EVENT_IOC_ENABLE, 0);
    }

    if (fd1_ != -1) { // stat
      ioctl(fd1_, PERF_EVENT_IOC_ENABLE, PERF_IOC_FLAG_GROUP);
    }

    ([&] { // time
      if constexpr (requires { static_cast<TEvents&>(events_).start(); }) {
        static_cast<TEvents&>(events_).start();
      }
    }(), ...);

    startLabel_ = std::uint64_t(StartLabel);
    core::code::label<StartLabel>();

    return std::integral_constant<decltype(StartLabel), StartLabel>{};
  }

  template<auto StopLabel = +[]{}>
  constexpr auto stop() noexcept {
    stopLabel_ = std::uint64_t(StopLabel);
    core::code::label<StopLabel>();

    ([&] { // time
      if constexpr (requires { static_cast<TEvents&>(events_).stop(); }) {
        static_cast<TEvents&>(events_).stop();
      }
    }(), ...);

    if (fd2_ != -1) { // record
      ioctl(fd2_, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);
    }

    if (fd1_ != -1) { // stat
      utility::verify(read(fd1_, &stat_, sizeof(stat_)) == sizeof(stat_));
      ioctl(fd1_, PERF_EVENT_IOC_DISABLE, PERF_IOC_FLAG_GROUP);
    }

    if (fd_ != -1) { // trace
      ioctl(fd_, PERF_EVENT_IOC_DISABLE, 0);
    }

    return std::integral_constant<decltype(StopLabel), StopLabel>{};
  }

  constexpr void reset() noexcept {
    if (fd2_ != -1) { // record
      ioctl(fd2_, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
    }

    if (fd_ != -1) { // trace
      ioctl(fd_, PERF_EVENT_IOC_RESET, 0);
    }

    if (fd1_ != -1) { // stat
      ioctl(fd1_, PERF_EVENT_IOC_RESET, PERF_IOC_FLAG_GROUP);
    }
  }

  template<class... Ts>
      requires ([]<class T> { return (std::same_as<T, TEvents> or ...); }.template operator()<Ts>() and ...) and
     (requires { Ts::name(); typename Ts::value_type; } and ...)
  [[nodiscard]] constexpr auto operator[](Ts...) const noexcept {
    utility::tuple results{utility::fixed_named<Ts::name(), std::vector<typename Ts::value_type>>{}...};

    constexpr auto value = [](const auto& v, const auto id) {
      const auto found = std::find_if(std::begin(v), std::end(v), [&](const auto& data) { return data.id == id; });
      utility::verify(found != std::end(v));
      return found->value;
    };

    ([&] {
      if constexpr (requires (Ts t) { t.start(); t.stop(); *t; }) {
        utility::overload{
          [&]<class T, class U>(utility::fixed_named<Ts::name(), T>* v, const utility::fixed_named<Ts::name(), U>* t) {
            v->push_back(**t);
          },
         [](...) { },
        }(&results, &events_);
      } else if constexpr (std::string_view(Ts::name()).starts_with("stat.")) {
        utility::verify(stat_.size == (std::string_view(TEvents::name()).starts_with("stat.") + ...));
        utility::verify(stat_.total_time_enabled  > 0u and stat_.total_time_running > 0u);
        const auto correction = double(stat_.total_time_enabled) / double(stat_.total_time_running);
        utility::overload{
          [&]<class T>(utility::fixed_named<Ts::name(), T>* v) {
            v->push_back(value(stat_.values, ids_.at(std::string_view(Ts::name()))) * correction);
          },
         [](...) { },
        }(&results);
      } else if constexpr (std::string_view(Ts::name()).starts_with("record.")) {
        const auto mmap_page = reinterpret_cast<perf_event_mmap_page*>(buffer2_);
        const auto begin = reinterpret_cast<const std::byte*>(buffer2_) + perf::info::sys::page_size();
        const auto end = begin + mmap_page->data_head;
        for (auto it = begin; it < end; it += reinterpret_cast<const perf_event_header*>(it)->size) {
          if (reinterpret_cast<const perf_event_header*>(it)->type != PERF_RECORD_SAMPLE) {
            continue;
          }

          const auto& data = *reinterpret_cast<const record*>(it + sizeof(perf_event_header));
          utility::verify(data.size == (std::string_view(TEvents::name()).starts_with("record.") + ...));
          utility::verify(data.ip and data.total_time_enabled and data.total_time_running);
          const auto correction = double(data.total_time_enabled) / double(data.total_time_running);
          utility::overload{
            [&]<class T>(utility::fixed_named<Ts::name(), T>* v) {
              // todo region boundries
              v->push_back({data.ip, value(data.values, ids_.at(std::string_view(Ts::name()))) * correction});
            },
           [](...) { },
          }(&results);

          utility::verify(sizeof(data) + sizeof(std::uint64_t) == reinterpret_cast<const perf_event_header*>(it)->size);
        }
      }
    }(), ...);

    if constexpr ((std::string_view(Ts::name()).starts_with("trace.") or ...)) {
      static constexpr auto memcpy =
        [](std::uint8_t* buffer, std::size_t size, const pt_asid*,
           std::uint64_t address, [[maybe_unused]] void* context) -> int {
          std::memcpy(buffer, reinterpret_cast<void*>(address), size);
          return size;
        };

      const auto start = core::code::labels[startLabel_];
      const auto stop = core::code::labels[stopLabel_];

      /// https://github.com/intel/libipt/blob/master/doc/man/pt_config.3.md
      pt_cpu cpu{
        .vendor = __builtin_cpu_is("intel") ? pcv_intel : pcv_unknown,
        .family = target_.vendor.family,
        .model = target_.vendor.model,
        .stepping = target_.vendor.stepping,
      };
      pt_config config{};
      config.size = sizeof(pt_config);
      config.begin = reinterpret_cast<std::uint8_t*>(aux_);
      config.end = reinterpret_cast<std::uint8_t*>(aux_) + target_.aux_size;
      config.cpu = cpu;

      auto status = pt_cpu_errata(&config.errata, &config.cpu);
      utility::verify(status >= 0, pt_errstr(pt_errcode(status)));

      auto *decoder = pt_insn_alloc_decoder(&config);
      utility::scoped _{
        .on_entry = [&] { utility::verify(bool(decoder)); },
        .on_exit  = [&] { pt_insn_free_decoder(decoder); },
      };

      auto *image = pt_insn_get_image(decoder);
      status = pt_image_set_callback(image, memcpy, nullptr);
      utility::verify(status >= 0, pt_errstr(pt_errcode(status)));

      status = pt_insn_sync_forward(decoder);
      utility::verify(status >= 0, pt_errstr(pt_errcode(status)));

      auto instruction = pt_insn{};
      auto trace = false;

      while (status != -pte_eos) {
        while (status & pts_event_pending) {
          pt_event event{};
          status = pt_insn_event(decoder, &event, sizeof(event));
          utility::verify(status >= 0, pt_errstr(pt_errcode(status)));
        }

        /// https://github.com/intel/libipt/blob/master/doc/man/pt_insn_next.3.md
        status = pt_insn_next(decoder, &instruction, sizeof(instruction));
        if (status == -pte_eos) [[unlikely]] {
          break;
        }
        utility::verify(status >= 0, pt_errstr(pt_errcode(status)));

        if (trace = (trace or instruction.ip == start) and instruction.ip != stop; trace) {
          utility::overload{
            [&]<class T>(utility::fixed_named<"trace.instructions", T>* v) {
              v->push_back({.ip = instruction.ip, .size = instruction.size});
            },
            [](...) { },
          }(&results);

          utility::overload{
            [&]<class T>(utility::fixed_named<"trace.cycles", T>* v) {
              std::uint64_t tsc{};
              pt_insn_time(static_cast<pt_insn_decoder*>(decoder), &tsc, nullptr, nullptr);
              utility::verify(status >= 0, pt_errstr(pt_errcode(status)));
              v->push_back(tsc);
            },
            [](...) { },
          }(&results);
        }
      }
    }

    return results;
  }

  [[nodiscard]] constexpr auto operator[]() const noexcept {
    return this->operator[](TEvents{}...);
  }

 private:
  std::uint64_t startLabel_{};
  std::uint64_t stopLabel_{};
  target target_{};
  utility::tuple<TEvents...> events_{};/// todo value_type
  std::unordered_map<std::string_view, std::uint64_t> ids_{};
  stat stat_{};
  std::int32_t fd_{-1};
  std::int32_t fd1_{-1};
  std::int32_t fd2_{-1};
  void* buffer_{};
  void* buffer2_{};
  void* aux_{};
};

template<class... TFeatures>
class analyzer final {
 public:
  /**
   * llc -march=x86 -mcpu=help
   */
  struct arch {
    /// x86_64-pc-linux-gnu, arm-none-eabi, aarch64-unknown-linux-gnu, ...
    std::string triple = ::llvm::Triple::normalize(::llvm::sys::getDefaultTargetTriple());

    /// alderlake, westmere, btver2, ...
    std::string cpu = ::llvm::sys::getHostCPUName().str();

    /// +bmi2, -avx2, +avx512, ... # default: available features of the current cpu
    std::string features{};

    /// att: 'movl %eax, %ebx', intel: 'mov ebx, eax' # default: intel
    enum class syntax { att, intel } syntax = syntax::intel;

    /// overrides processor dispatch width
    std::size_t dispatch_width{};

    /// overrdies number of entries in the micro-op queue
    std::size_t micro_op_queue{};

    /// overrdies maximum throughput from the decoders (instructions per cycle)
    std::size_t decoder_throughput{};

    /// overrides maximum number of physical registers which can be used for register mappings
    std::size_t register_file_size{};

    /// overrides size of the load queue
    std::size_t load_queue_size{};

    /// overrides size of the store queue
    std::size_t store_queue_size{};

    /// loads and stores do/do not alias # default: no alias
    bool assume_no_alias = true;
  };

  constexpr analyzer(const TFeatures&...) { }

  constexpr decltype(auto) operator<<(const auto& region) { }

  template<class... Ts>
  [[nodiscard]] constexpr auto operator[](const Ts&... ts) const {
    return utility::tuple();
  }

 private:
};

template<class... TRunners>
class runner final {
  template<auto Tag, class T = class none, auto N = 0ul, class... Ts, auto = []{}>
  [[nodiscard]] constexpr auto version() {
    if constexpr (std::same_as<T, none>) {
      if constexpr (requires { get(utility::detail::info<Tag, N>{}); }) {
        return version<Tag, T, N + 1ul, Ts..., decltype(get(utility::detail::info<Tag, N>{}))>();
      } else {
        return utility::type_list<typename Ts::type...>{};
      }
    } else if constexpr (requires { get(utility::detail::info<Tag, N>{}); }) {
      return version<Tag, T, N + 1ul>();
    } else {
      utility::detail::meta<T, Tag, N>();
      return N;
    }
  }

 public:
  constexpr explicit runner(TRunners... ts)
    : runners{ts...}
  { }

  auto& operator()(auto&& fn, auto&&... ts) {
    constexpr auto insert = utility::overload{
      [](auto insert, auto& d, auto t) { d[t.name()] = t; },
      []<class... Ts>(auto insert, auto& d, utility::tuple<Ts...> t) {
        (insert(d, static_cast<Ts>(t)), ...);
      },
    };
    data.push_back({std::string("fn/runner"), {}});
    (insert(data.back().second, static_cast<TRunners&>(runners)(fn, ts...)), ...);
    return *this;
  }

  template<class... Ts>
  auto operator[](Ts... ts) const {
    std::vector<std::pair<std::string, utility::tuple<Ts...>>> v{};
    v.reverse(data.size());
    for (const auto& [name, data] : data) {
        v.emplace_back(name, utility::tuple(std::any_cast<Ts>(data.at(ts.name()))...));
    }
    return v;
  }

 private:
  utility::tuple<TRunners...> runners{};
  std::vector<std::pair<std::string, std::unordered_map<std::string, std::any>>> data{};
};

namespace bench {
template<class... Ts>
struct latency {
    latency(Ts...) {}
    auto operator()(auto fn, auto...) {
        profiler p{Ts{}...};
        analyzer a{};
        return utility::tuple(p[], a[]);
    }
};

namespace policy {
  // seq
  // unseq
  // unroll
  // par
  // omp
  // cuda
} // namespace policy

struct throughput {
};

inline constexpr auto baseline = [](auto&& fn) {
  return utility::make_fixed_named<"baseline">(fn);
};
} // namespace bench
} // namespace perf

#if PERF_LINUX == 1
namespace perf::inline v1_0_0 {
namespace stat {
  namespace aux {
    template<class TRatio, class T = double>
    struct duration {
      using value_type = std::chrono::duration<T, TRatio>;

      constexpr duration() = default;
      constexpr duration(const auto& value)
        requires requires { value_type(value); }
        : value(value)
      { }

      [[nodiscard]] constexpr auto count() const {
        return value.count();
      }

      [[nodiscard]] constexpr operator auto() const {
        return count();
      }

      value_type value{};
    };

    struct event {
      using value_type = utility::strong_alias<double>;
      std::uint32_t type{};
      std::array<std::uint64_t, 3u> config{};                       /// perf_event_attr.{config1, config2, config3}
      enum priority { low, medium, high } priority = priority::low; /// high = group leader
    };
  } // namespace aux

  template<class T>
    requires requires { T::period::den; } and (T::period::den == std::nano::den)
  struct chrono {
    using value_type = aux::duration<std::nano>;

    constexpr auto start() { start_ = T::now(); }
    constexpr auto stop()  { stop_ = T::now(); }

    [[nodiscard]] constexpr auto operator*() const {
      return value_type{stop_ - start_};
    }

   private:
    T::time_point start_{};
    T::time_point stop_{};
  };

  #if PERF_LINUX == 1
  /**
   * clock_gettime overhead is not stable # may lock, may call syscall
   * - /sys/devices/system/clocksource/clocksource0/current_clocksource
   * @tparam ClockId
   *  CLOCK_MONOTONIC
   *  CLOCK_MONOTONIC_RAW
   *  CLOCK_REALTIME
   *  CLOCK_REALTIME_COARSE
   *  CLOCK_PROCESS_CPUTIME_ID
   *  CLOCK_THREAD_CPUTIME_ID
   */
  template<clockid_t ClockId>
  struct clock {
    using value_type = aux::duration<std::nano>;

    constexpr auto start() { clock_gettime(ClockId, &start_); }
    constexpr auto stop()  { clock_gettime(ClockId, &stop_); }

    [[nodiscard]] constexpr auto operator*() const {
      return value_type{
        (stop_.tv_sec - start_.tv_sec) * 1e9 + (stop_.tv_nsec - start_.tv_nsec)
      };
    }

   private:
    timespec start_{};
    timespec stop_{};
  };
  #endif // PERF_LINUX

  #if __has_builtin(__builtin_ia32_rdtsc)
  /**
   * https://en.wikipedia.org/wiki/Time_Stamp_Counter
   * https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#text=rdtsc
   */
  struct rdtsc {
    using GHz = utility::strong_alias<double>;
    using value_type = aux::duration<std::nano>;

    constexpr void start() {
      start_ = __builtin_ia32_rdtsc(); /// no serialization
    }

    constexpr void stop() {
      unsigned int aux{};
      stop_ = __builtin_ia32_rdtscp(&aux); /// partial serialization
    }

    [[nodiscard]] constexpr auto operator*() const {
      return value_type{(stop_ - start_) / freq()};
    }

   private:
    std::uint64_t start_{};
    std::uint64_t stop_{};
    [[nodiscard]] static auto freq() -> GHz;
  };

  auto rdtsc::freq() -> GHz {
    static auto freq = []<std::size_t N = 3u, std::size_t ms = 10u> {
      auto freq = 0.;
      rdtsc t{};
      for (auto i = 0u; i < N; ++i) {
        const auto start = std::chrono::steady_clock::now();
        std::chrono::steady_clock::time_point stop{};
        const auto min = start + std::chrono::milliseconds(ms);

        t.start();
        for (;;) {
          stop = std::chrono::steady_clock::now();
          t.stop();
          if (stop >= min) {
            break;
          }
        }

        freq = std::max(freq, (t.stop_ - t.start_) /
          aux::duration<std::nano>(stop - start)
        );
      }
      return freq;
    }();
    return {freq};
  }
  #endif // __builtin_ia32_rdtsc

  /// monotonic time # guranateed to be always increasing
  inline constexpr auto steady_clock = utility::fixed_named<"time.steady_clock", chrono<std::chrono::steady_clock>>{};

  /// highest available resolution clock # may not be steady
  inline constexpr auto high_resolution_clock = utility::fixed_named<"time.high_resolution_clock", chrono<std::chrono::high_resolution_clock>>{};

  #if PERF_LINUX == 1
  /// user time + sys time
  inline constexpr auto cpu_time = utility::fixed_named<"time.cpu_time", clock<CLOCK_PROCESS_CPUTIME_ID>>{};

  /// cpu time for the current thread
  inline constexpr auto thread_time = utility::fixed_named<"time.thread_time", clock<CLOCK_THREAD_CPUTIME_ID>>{};

  /// wall clock time
  /// - backed by tsc: yes if /sys/devices/system/clocksource/clocksource0/current_clocksource is tsc
  /// - vdso: yes
  /// - ntp: no
  inline constexpr auto real_time = utility::fixed_named<"time.real_time", clock<CLOCK_REALTIME>>{};

  /// elapsed time since boot # guranateed to be always increasing
  /// - backed by tsc: yes if /sys/devices/system/clocksource/clocksource0/current_clocksource is tsc
  /// - vdso: yes
  /// - ntp: no
  inline constexpr auto monotonic_time = utility::fixed_named<"time.monotonic_time", clock<CLOCK_MONOTONIC>>{};

  /// raw hardware time # guranateed to be always increasing
  /// - backed by tsc: yes if /sys/devices/system/clocksource/clocksource0/current_clocksource is tsc
  /// - vdso: yes
  /// - ntp: no
  inline constexpr auto raw_time = utility::fixed_named<"time.raw_time", clock<CLOCK_MONOTONIC_RAW>>{};
  #endif // PERF_LINUX

  #if __has_builtin(__builtin_ia32_rdtsc)
  /// time-stamp-counter # https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#text=rdtsc
  inline constexpr auto tsc = utility::fixed_named<"time.tsc", struct rdtsc>{};
  #endif // __builtin_ia32_rdtsc

  /**
   * perf list                        - shows available events
   * perf stat -vv -e {event} sleep 0 - finds config values for given event
   * https://perfmon-events.intel.com - intel's list of events per architecture
   */
  inline constexpr auto cpu_clock = utility::constant<utility::make_fixed_named<"stat.cpu_clock">(aux::event{PERF_TYPE_SOFTWARE, {PERF_COUNT_SW_CPU_CLOCK}})>{};
  inline constexpr auto task_clock = utility::constant<utility::make_fixed_named<"stat.task_clock">(aux::event{PERF_TYPE_SOFTWARE, {PERF_COUNT_SW_TASK_CLOCK}})>{};
  inline constexpr auto page_faults = utility::constant<utility::make_fixed_named<"stat.page_faults">(aux::event{PERF_TYPE_SOFTWARE, {PERF_COUNT_SW_PAGE_FAULTS}})>{};
  inline constexpr auto faults = utility::constant<utility::make_fixed_named<"stat.faults">(aux::event{PERF_TYPE_SOFTWARE, {PERF_COUNT_SW_PAGE_FAULTS}})>{};
  inline constexpr auto major_faults = utility::constant<utility::make_fixed_named<"stat.major_faults">(aux::event{PERF_TYPE_SOFTWARE, {PERF_COUNT_SW_PAGE_FAULTS_MAJ}})>{};
  inline constexpr auto minor_faults = utility::constant<utility::make_fixed_named<"stat.minor_faults">(aux::event{PERF_TYPE_SOFTWARE, {PERF_COUNT_SW_PAGE_FAULTS_MIN}})>{};
  inline constexpr auto alignment_faults = utility::constant<utility::make_fixed_named<"stat.alignment_faults">(aux::event{PERF_TYPE_SOFTWARE, {PERF_COUNT_SW_ALIGNMENT_FAULTS}})>{};
  inline constexpr auto emulation_faults = utility::constant<utility::make_fixed_named<"stat.emulation_faults">(aux::event{PERF_TYPE_SOFTWARE, {PERF_COUNT_SW_EMULATION_FAULTS}})>{};
  inline constexpr auto context_switches = utility::constant<utility::make_fixed_named<"stat.context_switches">(aux::event{PERF_TYPE_SOFTWARE, {PERF_COUNT_SW_CONTEXT_SWITCHES}})>{};
  inline constexpr auto cgroup_switches = utility::constant<utility::make_fixed_named<"stat.cgroup_switches">(aux::event{PERF_TYPE_SOFTWARE, {PERF_COUNT_SW_CGROUP_SWITCHES}})>{};
  inline constexpr auto cpu_migrations = utility::constant<utility::make_fixed_named<"stat.cpu_migrations">(aux::event{PERF_TYPE_SOFTWARE, {PERF_COUNT_SW_CPU_MIGRATIONS}})>{};
  inline constexpr auto migrations = utility::constant<utility::make_fixed_named<"stat.migrations">(aux::event{PERF_TYPE_SOFTWARE, {PERF_COUNT_SW_CPU_MIGRATIONS}})>{};
  inline constexpr auto cycles = utility::constant<utility::make_fixed_named<"stat.cycles">(aux::event{PERF_TYPE_HARDWARE, {PERF_COUNT_HW_CPU_CYCLES}})>{};
  inline constexpr auto instructions = utility::constant<utility::make_fixed_named<"stat.instructions">(aux::event{PERF_TYPE_HARDWARE, {PERF_COUNT_HW_INSTRUCTIONS}})>{};
  inline constexpr auto branch_misses = utility::constant<utility::make_fixed_named<"stat.branch_misses">(aux::event{PERF_TYPE_HARDWARE, {PERF_COUNT_HW_BRANCH_MISSES}})>{};
  inline constexpr auto bus_cycles = utility::constant<utility::make_fixed_named<"stat.bus_cycles">(aux::event{PERF_TYPE_HARDWARE, {PERF_COUNT_HW_BUS_CYCLES}})>{};
  inline constexpr auto cache_misses = utility::constant<utility::make_fixed_named<"stat.cache_misses">(aux::event{PERF_TYPE_HARDWARE, {PERF_COUNT_HW_CACHE_MISSES}})>{};
  inline constexpr auto cache_references = utility::constant<utility::make_fixed_named<"stat.cache_references">(aux::event{PERF_TYPE_HARDWARE, {PERF_COUNT_HW_CACHE_REFERENCES}})>{};
  inline constexpr auto branches = utility::constant<utility::make_fixed_named<"stat.branches">(aux::event{PERF_TYPE_HARDWARE, {PERF_COUNT_HW_BRANCH_INSTRUCTIONS}})>{};
  inline constexpr auto branch_instructions = utility::constant<utility::make_fixed_named<"stat.branch_instructions">(aux::event{PERF_TYPE_HARDWARE, {PERF_COUNT_HW_BRANCH_INSTRUCTIONS}})>{};
  inline constexpr auto stalled_cycles_backend = utility::constant<utility::make_fixed_named<"stat.stalled_cycles_backend">(aux::event{PERF_TYPE_HARDWARE, {PERF_COUNT_HW_STALLED_CYCLES_BACKEND}})>{};
  inline constexpr auto idle_cycles_backend = utility::constant<utility::make_fixed_named<"stat.idle_cycles_backend">(aux::event{PERF_TYPE_HARDWARE, {PERF_COUNT_HW_STALLED_CYCLES_BACKEND}})>{};
  inline constexpr auto stalled_cycles_frontend = utility::constant<utility::make_fixed_named<"stat.stalled_cycles_frontend">(aux::event{PERF_TYPE_HARDWARE, {PERF_COUNT_HW_STALLED_CYCLES_FRONTEND}})>{};
  inline constexpr auto idle_cycles_frontend = utility::constant<utility::make_fixed_named<"stat.idle_cycles_frontend">(aux::event{PERF_TYPE_HARDWARE, {PERF_COUNT_HW_STALLED_CYCLES_FRONTEND}})>{};
  inline constexpr auto llc_misses = utility::constant<utility::make_fixed_named<"stat.LLC_misses">(aux::event{PERF_TYPE_HARDWARE, {PERF_COUNT_HW_CACHE_MISSES}})>{};
  inline constexpr auto l1_misses = utility::constant<utility::make_fixed_named<"stat.L1_misses">(aux::event{PERF_TYPE_HW_CACHE, {PERF_COUNT_HW_CACHE_L1D | (PERF_COUNT_HW_CACHE_OP_READ << 8u) | (PERF_COUNT_HW_CACHE_RESULT_MISS << 16u)}})>{};
  inline constexpr auto l1_dcache_loads = utility::constant<utility::make_fixed_named<"stat.L1_dcache_loads">(aux::event{PERF_TYPE_HW_CACHE, {PERF_COUNT_HW_CACHE_L1D | (PERF_COUNT_HW_CACHE_OP_READ << 8u) | (PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16u)}})>{};
  inline constexpr auto l1_dcache_load_misses = utility::constant<utility::make_fixed_named<"stat.L1_dcache_load_misses">(aux::event{PERF_TYPE_HW_CACHE, {PERF_COUNT_HW_CACHE_L1D | (PERF_COUNT_HW_CACHE_OP_READ << 8u) | (PERF_COUNT_HW_CACHE_RESULT_MISS << 16u)}})>{};
  inline constexpr auto l1_icache_loads = utility::constant<utility::make_fixed_named<"stat.L1_icache_loads">(aux::event{PERF_TYPE_HW_CACHE, {PERF_COUNT_HW_CACHE_L1I | (PERF_COUNT_HW_CACHE_OP_READ << 8u) | (PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16u)}})>{};
  inline constexpr auto l1_icache_load_misses = utility::constant<utility::make_fixed_named<"stat.L1_icache_load_misses">(aux::event{PERF_TYPE_HW_CACHE, {PERF_COUNT_HW_CACHE_L1I | (PERF_COUNT_HW_CACHE_OP_READ << 8u) | (PERF_COUNT_HW_CACHE_RESULT_MISS << 16u)}})>{};
  inline constexpr auto dtlb_loads = utility::constant<utility::make_fixed_named<"stat.dTLB_loads">(aux::event{PERF_TYPE_HW_CACHE, {PERF_COUNT_HW_CACHE_DTLB | (PERF_COUNT_HW_CACHE_OP_READ << 8u) | (PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16u)}})>{};
  inline constexpr auto dtlb_load_misses = utility::constant<utility::make_fixed_named<"stat.dTLB_load_misses">(aux::event{PERF_TYPE_HW_CACHE, {PERF_COUNT_HW_CACHE_DTLB | (PERF_COUNT_HW_CACHE_OP_READ << 8u) | (PERF_COUNT_HW_CACHE_RESULT_MISS << 16u)}})>{};
  inline constexpr auto itlb_loads = utility::constant<utility::make_fixed_named<"stat.iTLB_loads">(aux::event{PERF_TYPE_HW_CACHE, {PERF_COUNT_HW_CACHE_ITLB | (PERF_COUNT_HW_CACHE_OP_READ << 8u) | (PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16u)}})>{};
  inline constexpr auto itlb_load_misses = utility::constant<utility::make_fixed_named<"stat.iTLB_load_misses">(aux::event{PERF_TYPE_HW_CACHE, {PERF_COUNT_HW_CACHE_ITLB | (PERF_COUNT_HW_CACHE_OP_READ << 8u) | (PERF_COUNT_HW_CACHE_RESULT_MISS << 16u)}})>{};

  #if 0
  namespace mca {
    struct cycles {
      using value_type = strong_alias<double>;

      std::size_t iterations = 1u; /// number of iterations to simulate

      [[nodiscard]] constexpr auto operator()(const std::ranges::range auto& instructions, auto& llvm) const {
        std::vector<std::unique_ptr<::llvm::mca::Instruction>> lowered_sequence{};
        const ::llvm::SmallVector<::llvm::mca::Instrument*> instruments{};
        for (const auto& instruction : instructions) {
          ::llvm::MCInst inst{};
          std::size_t size{};
          verify(llvm.disassembler->getInstruction(
            inst,
            size,
            ::llvm::ArrayRef<std::uint8_t>{
              reinterpret_cast<const std::uint8_t*>(instruction.ip),
              reinterpret_cast<const std::uint8_t*>(instruction.ip) + instruction.size
            },
            instruction.ip,
            ::llvm::nulls()
          ) == ::llvm::MCDisassembler::DecodeStatus::Success);
          lowered_sequence.emplace_back(
            std::move(llvm.instruction_builder->createInstruction(inst, instruments).get())
          );
        }

        if (lowered_sequence.empty()) {
          return value_type{};
        }

        ::llvm::mca::CircularSourceMgr mgr(lowered_sequence, iterations);
        ::llvm::mca::CustomBehaviour custom_behavior{*llvm.subtarget_info, mgr, *llvm.instruction_info};
        ::llvm::mca::PipelineOptions options(
          llvm.arch.micro_op_queue,
          llvm.arch.decoder_throughput,
          llvm.arch.dispatch_width,
          llvm.arch.register_file_size,
          llvm.arch.load_queue_size,
          llvm.arch.store_queue_size,
          llvm.arch.assume_no_alias
        );
        ::llvm::mca::Context mca{*llvm.register_info, *llvm.subtarget_info};
        auto pipeline = mca.createDefaultPipeline(options, mgr, custom_behavior);

        value_type cycles{};
        handler handler{cycles.value};

        pipeline->addEventListener(std::addressof(handler));
        verify(bool(pipeline->run()));

        return cycles;
      }

     private:
      template<class T>
      struct handler : ::llvm::mca::View {
        constexpr explicit handler(T& cycles)
          : cycles_{cycles}
        { }

        //todo
        //constexpr void onEvent(const ::llvm::mca::HWInstructionEvent& event) override {
          //if (event.Type != ::llvm::mca::HWInstructionEvent::Retired or
              //event.IR.getSourceIndex() >= Source.size()) {
            //return;
          //}
          //uops += *event.IR.getInstruction().getDesc().NumMicroOps;
        //}

        constexpr void onCycleEnd() override { ++cycles_; }

        ::llvm::StringRef getNameAsString() const override { return {}; }
        void printView(::llvm::raw_ostream&) const override { }

       private:
        T& cycles_;
      };
    };

    //todo
    inline constexpr auto cycles = fixed_named<"stat.mca.cycles", struct cycles>{};
    inline constexpr auto instructions = fixed_named<"stat.mca.cycles", struct cycles>{};
    inline constexpr auto uops = fixed_named<"stat.mca.cycles", struct cycles>{};
  } // namespace mca
  #endif

  // use strong_alias, that sould be array{1}
  struct operations { using value_type = double; value_type value{}; };
  inline constexpr auto operations = utility::fixed_named<"bench.operations", struct operations>{};

  // use strong_alias
  struct samples { using value_type = double; value_type value{}; };
  inline constexpr auto samples = utility::fixed_named<"bench.samples", struct samples>{};
} // namespace stat

namespace record {
  namespace aux {
    struct mem {
      std::uint64_t ip{};
      std::uint64_t dst{};
      std::uint64_t src{};

      struct cache {
        enum {
          hit       = 0b000001,
          miss      = 0b000010,
          uncached  = 0b000100,
        } access{};
        enum {
          L1        = 0b000001,
          L2        = 0b000010,
          L3        = 0b000100,
          LFB       = 0b001000, /// line fill buffer
          RAM       = 0b010000,
          IO        = 0b100000,
        } level{};
      } cache{};

      struct tlb {
        enum {
          hit       = 0b000001,
          miss      = 0b000010,
        } access{};
        enum {
          L1        = 0b000001,
          L2        = 0b000010,
          WK        = 0b000100,
          OS        = 0b001000,
        } level{};
      } tlb{};

      /**
       * https://en.wikipedia.org/wiki/MESI_protocol
       * https://en.wikipedia.org/wiki/MOESI_protocol
       */
      struct snoop {
        enum {
          none      = 0b000001, /// resolved in local cache
          hit       = 0b000010, /// data found in peer core's cache
          miss      = 0b000100, /// snoop was issued but no core had the data
          modify    = 0b001000, /// data found modified in another cache
          fwd       = 0b010000, /// data was forwarded
          peer      = 0b100000, /// remote cache access
        } access{};
      } snoop{};

      constexpr mem() = default;
      constexpr explicit mem(const auto& data, const auto& src)
        : ip{data.ip}
        , dst{data.dst}
        , src{data.src}
        , cache{
          .access = decltype(cache::access)(
               to(src.mem_lvl, PERF_MEM_LVL_UNC, cache::uncached)
             | to(src.mem_lvl, PERF_MEM_LVL_HIT, cache::hit)
             | to(src.mem_lvl, PERF_MEM_LVL_MISS, cache::miss)
           ),
          .level = decltype(cache::level)(
               to(src.mem_lvl, PERF_MEM_LVL_L1, cache::L1)
             | to(src.mem_lvl, PERF_MEM_LVL_L2, cache::L2)
             | to(src.mem_lvl, PERF_MEM_LVL_L3, cache::L3)
             | to(src.mem_lvl, PERF_MEM_LVL_LFB, cache::LFB)
             | to(src.mem_lvl, PERF_MEM_LVL_LOC_RAM, cache::RAM)
             | to(src.mem_lvl, PERF_MEM_LVL_IO, cache::IO)
           )
          }
        , tlb{
          .access = decltype(tlb::access)(
               to(src.mem_dtlb, PERF_MEM_TLB_HIT, tlb::hit)
             | to(src.mem_dtlb, PERF_MEM_TLB_MISS, tlb::miss)
           ),
          .level = decltype(tlb::level)(
               to(src.mem_dtlb, PERF_MEM_TLB_L1, tlb::L1)
             | to(src.mem_dtlb, PERF_MEM_TLB_L2, tlb::L2)
             | to(src.mem_dtlb, PERF_MEM_TLB_WK, tlb::WK)
             | to(src.mem_dtlb, PERF_MEM_TLB_OS, tlb::OS)
           )
          }
        , snoop{
          .access = decltype(snoop::access)(
               to(src.mem_snoop, PERF_MEM_SNOOP_NONE, snoop::none)
             | to(src.mem_snoop, PERF_MEM_SNOOP_HIT, snoop::hit)
             | to(src.mem_snoop, PERF_MEM_SNOOP_MISS, snoop::miss)
             | to(src.mem_snoop, PERF_MEM_SNOOP_HITM, snoop::hit | snoop::modify)
             | to(src.mem_snoopx, PERF_MEM_SNOOPX_FWD, snoop::fwd)
             #ifdef PERF_MEM_SNOOPX_PEER
             | to(src.mem_snoopx, PERF_MEM_SNOOPX_PEER, snoop::peer)
             #endif
           )
          }
      { }

      static constexpr auto to = [](const auto& value, const auto lhs, const auto rhs) {
        return (value & lhs) ? rhs : decltype(rhs){};
      };
    };

    struct event {
      using value_type = struct record {
        std::uint64_t ip{};
        utility::strong_alias<double> value{};
      };
      std::uint32_t type{};
      std::array<std::uint64_t, 3u> config{}; /// perf_event_attr.{config1, config2, config3}
    };

    struct mem_event {
      using value_type = mem;
      std::uint32_t type{};
      struct {
        std::array<std::uint64_t, 3u>(*fn)(){};
        [[nodiscard]] constexpr operator auto() const { return fn(); }
        [[nodiscard]] constexpr auto operator [](std::size_t i) const { return fn()[i]; }
      } config{};
      std::uint32_t operation{};
    };

    template<utility::fixed_string Name, utility::fixed_string Fmt = "event=%zx,umask=%zx">
    inline constexpr auto config = [] -> std::array<std::uint64_t, 3u> {
      auto&& cfg = perf::info::sys::hw<Fmt>(std::format("/sys/bus/event_source/devices/cpu/events/{}", std::string_view(Name))).or_else(
        [] { return perf::info::sys::hw<Fmt>(std::format("/sys/bus/event_source/devices/cpu_core/events/{}", std::string_view(Name))); }
      );
      utility::verify(cfg.has_value(), std::format("'{}' not found!", std::string_view(Name)));
      return {((*cfg)[1u] << CHAR_BIT) | (*cfg)[0u], cfg->size() == 3u ? (*cfg)[2u] : std::uint64_t{}};
    };
  } // namespace aux

  /**
   * perf list # shows available events
   * perf stat -vv -e {event} sleep 0 # finds config values for given event
   */
  inline constexpr auto cpu_clock = utility::constant<utility::make_fixed_named<"record.cpu_clock">(aux::event{PERF_TYPE_SOFTWARE, {PERF_COUNT_SW_CPU_CLOCK}})>{};
  inline constexpr auto task_clock = utility::constant<utility::make_fixed_named<"record.task_clock">(aux::event{PERF_TYPE_SOFTWARE, {PERF_COUNT_SW_TASK_CLOCK}})>{};
  inline constexpr auto page_faults = utility::constant<utility::make_fixed_named<"record.page_faults">(aux::event{PERF_TYPE_SOFTWARE, {PERF_COUNT_SW_PAGE_FAULTS}})>{};
  inline constexpr auto faults = utility::constant<utility::make_fixed_named<"record.faults">(aux::event{PERF_TYPE_SOFTWARE, {PERF_COUNT_SW_PAGE_FAULTS}})>{};
  inline constexpr auto major_faults = utility::constant<utility::make_fixed_named<"record.major_faults">(aux::event{PERF_TYPE_SOFTWARE, {PERF_COUNT_SW_PAGE_FAULTS_MAJ}})>{};
  inline constexpr auto minor_faults = utility::constant<utility::make_fixed_named<"record.minor_faults">(aux::event{PERF_TYPE_SOFTWARE, {PERF_COUNT_SW_PAGE_FAULTS_MIN}})>{};
  inline constexpr auto alignment_faults = utility::constant<utility::make_fixed_named<"record.alignment_faults">(aux::event{PERF_TYPE_SOFTWARE, {PERF_COUNT_SW_ALIGNMENT_FAULTS}})>{};
  inline constexpr auto emulation_faults = utility::constant<utility::make_fixed_named<"record.emulation_faults">(aux::event{PERF_TYPE_SOFTWARE, {PERF_COUNT_SW_EMULATION_FAULTS}})>{};
  inline constexpr auto context_switches = utility::constant<utility::make_fixed_named<"record.context_switches">(aux::event{PERF_TYPE_SOFTWARE, {PERF_COUNT_SW_CONTEXT_SWITCHES}})>{};
  inline constexpr auto cgroup_switches = utility::constant<utility::make_fixed_named<"record.cgroup_switches">(aux::event{PERF_TYPE_SOFTWARE, {PERF_COUNT_SW_CGROUP_SWITCHES}})>{};
  inline constexpr auto cpu_migrations = utility::constant<utility::make_fixed_named<"record.cpu_migrations">(aux::event{PERF_TYPE_SOFTWARE, {PERF_COUNT_SW_CPU_MIGRATIONS}})>{};
  inline constexpr auto migrations = utility::constant<utility::make_fixed_named<"record.migrations">(aux::event{PERF_TYPE_SOFTWARE, {PERF_COUNT_SW_CPU_MIGRATIONS}})>{};
  inline constexpr auto cycles = utility::constant<utility::make_fixed_named<"record.cycles">(aux::event{PERF_TYPE_HARDWARE, {PERF_COUNT_HW_CPU_CYCLES}})>{};
  inline constexpr auto instructions = utility::constant<utility::make_fixed_named<"record.instructions">(aux::event{PERF_TYPE_HARDWARE, {PERF_COUNT_HW_INSTRUCTIONS}})>{};
  inline constexpr auto branch_misses = utility::constant<utility::make_fixed_named<"record.branch_misses">(aux::event{PERF_TYPE_HARDWARE, {PERF_COUNT_HW_BRANCH_MISSES}})>{};
  inline constexpr auto bus_cycles = utility::constant<utility::make_fixed_named<"record.bus_cycles">(aux::event{PERF_TYPE_HARDWARE, {PERF_COUNT_HW_BUS_CYCLES}})>{};
  inline constexpr auto cache_misses = utility::constant<utility::make_fixed_named<"record.cache_misses">(aux::event{PERF_TYPE_HARDWARE, {PERF_COUNT_HW_CACHE_MISSES}})>{};
  inline constexpr auto cache_references = utility::constant<utility::make_fixed_named<"record.cache_references">(aux::event{PERF_TYPE_HARDWARE, {PERF_COUNT_HW_CACHE_REFERENCES}})>{};
  inline constexpr auto branches = utility::constant<utility::make_fixed_named<"record.branches">(aux::event{PERF_TYPE_HARDWARE, {PERF_COUNT_HW_BRANCH_INSTRUCTIONS}})>{};
  inline constexpr auto branch_instructions = utility::constant<utility::make_fixed_named<"record.branch_instructions">(aux::event{PERF_TYPE_HARDWARE, {PERF_COUNT_HW_BRANCH_INSTRUCTIONS}})>{};
  inline constexpr auto stalled_cycles_backend = utility::constant<utility::make_fixed_named<"record.stalled_cycles_backend">(aux::event{PERF_TYPE_HARDWARE, {PERF_COUNT_HW_STALLED_CYCLES_BACKEND}})>{};
  inline constexpr auto idle_cycles_backend = utility::constant<utility::make_fixed_named<"record.idle_cycles_backend">(aux::event{PERF_TYPE_HARDWARE, {PERF_COUNT_HW_STALLED_CYCLES_BACKEND}})>{};
  inline constexpr auto stalled_cycles_frontend = utility::constant<utility::make_fixed_named<"record.stalled_cycles_frontend">(aux::event{PERF_TYPE_HARDWARE, {PERF_COUNT_HW_STALLED_CYCLES_FRONTEND}})>{};
  inline constexpr auto idle_cycles_frontend = utility::constant<utility::make_fixed_named<"record.idle_cycles_frontend">(aux::event{PERF_TYPE_HARDWARE, {PERF_COUNT_HW_STALLED_CYCLES_FRONTEND}})>{};
  inline constexpr auto llc_misses = utility::constant<utility::make_fixed_named<"record.LLC_misses">(aux::event{PERF_TYPE_HARDWARE, {PERF_COUNT_HW_CACHE_MISSES}})>{};
  inline constexpr auto l1_misses = utility::constant<utility::make_fixed_named<"record.L1_misses">(aux::event{PERF_TYPE_HW_CACHE, {PERF_COUNT_HW_CACHE_L1D | (PERF_COUNT_HW_CACHE_OP_READ << 8u) | (PERF_COUNT_HW_CACHE_RESULT_MISS << 16u)}})>{};
  inline constexpr auto l1_dcache_loads = utility::constant<utility::make_fixed_named<"record.L1_dcache_loads">(aux::event{PERF_TYPE_HW_CACHE, {PERF_COUNT_HW_CACHE_L1D | (PERF_COUNT_HW_CACHE_OP_READ << 8u) | (PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16u)}})>{};
  inline constexpr auto l1_dcache_load_misses = utility::constant<utility::make_fixed_named<"record.L1_dcache_load_misses">(aux::event{PERF_TYPE_HW_CACHE, {PERF_COUNT_HW_CACHE_L1D | (PERF_COUNT_HW_CACHE_OP_READ << 8u) | (PERF_COUNT_HW_CACHE_RESULT_MISS << 16u)}})>{};
  inline constexpr auto l1_icache_loads = utility::constant<utility::make_fixed_named<"record.L1_icache_loads">(aux::event{PERF_TYPE_HW_CACHE, {PERF_COUNT_HW_CACHE_L1I | (PERF_COUNT_HW_CACHE_OP_READ << 8u) | (PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16u)}})>{};
  inline constexpr auto l1_icache_load_misses = utility::constant<utility::make_fixed_named<"record.L1_icache_load_misses">(aux::event{PERF_TYPE_HW_CACHE, {PERF_COUNT_HW_CACHE_L1I | (PERF_COUNT_HW_CACHE_OP_READ << 8u) | (PERF_COUNT_HW_CACHE_RESULT_MISS << 16u)}})>{};
  inline constexpr auto dtlb_loads = utility::constant<utility::make_fixed_named<"record.dTLB_loads">(aux::event{PERF_TYPE_HW_CACHE, {PERF_COUNT_HW_CACHE_DTLB | (PERF_COUNT_HW_CACHE_OP_READ << 8u) | (PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16u)}})>{};
  inline constexpr auto dtlb_load_misses = utility::constant<utility::make_fixed_named<"record.dTLB_load_misses">(aux::event{PERF_TYPE_HW_CACHE, {PERF_COUNT_HW_CACHE_DTLB | (PERF_COUNT_HW_CACHE_OP_READ << 8u) | (PERF_COUNT_HW_CACHE_RESULT_MISS << 16u)}})>{};
  inline constexpr auto itlb_loads = utility::constant<utility::make_fixed_named<"record.iTLB_loads">(aux::event{PERF_TYPE_HW_CACHE, {PERF_COUNT_HW_CACHE_ITLB | (PERF_COUNT_HW_CACHE_OP_READ << 8u) | (PERF_COUNT_HW_CACHE_RESULT_ACCESS << 16u)}})>{};
  inline constexpr auto itlb_load_misses = utility::constant<utility::make_fixed_named<"record.iTLB_load_misses">(aux::event{PERF_TYPE_HW_CACHE, {PERF_COUNT_HW_CACHE_ITLB | (PERF_COUNT_HW_CACHE_OP_READ << 8u) | (PERF_COUNT_HW_CACHE_RESULT_MISS << 16u)}})>{};
  inline constexpr auto mem_loads = utility::constant<utility::make_fixed_named<"record.mem_loads">(aux::mem_event{PERF_TYPE_RAW, {aux::config<"mem-loads", "event=%zx,umask=%zx,ldlat=%zd">}, PERF_MEM_OP_LOAD})>{};
  inline constexpr auto mem_stores = utility::constant<utility::make_fixed_named<"record.mem_stores">(aux::mem_event{PERF_TYPE_RAW, {aux::config<"mem-stores">}, PERF_MEM_OP_STORE})>{};
} // namespace record

namespace trace {
  namespace aux {
    struct instruction {
      std::uint64_t ip{};
      std::uint64_t size{};
    };
    template<class T>
    struct event {
      using value_type = T;
      struct {
        std::size_t(*fn)(){};
        [[nodiscard]] constexpr operator auto() const { return fn(); }
      } value{};
    };
    template<utility::fixed_string Name, utility::fixed_string Fmt = "%zd">
    inline constexpr auto config = [] {
      return info::sys::hw<Fmt>(std::format("/sys/bus/event_source/devices/intel_pt/{}", std::string_view(Name))).value()[0u];
    };
  } // namespace aux
  inline constexpr auto instructions = utility::constant<utility::make_fixed_named<"trace.instructions">(aux::event<aux::instruction>{aux::config<"type">})>{};
  inline constexpr auto cycles = utility::constant<utility::make_fixed_named<"trace.cycles">(aux::event<std::uint64_t>{aux::config<"format/tsc", "config:%zd">})>{};
} // namespace trace
} // namespace perf
#endif // PERF_LINUX

#if PERF_LLVM == 1
namespace perf::inline v1_0_0 {
namespace mc {
  // assembly
  // latency
  // timeline
  // bottleneck
  // resource_pressure
} // namespace mc

namespace debug {
} // namespace debug
} // namespace perf
#endif // PERF_LLVM

#if PERF_IO == 1
namespace perf {
  // log
  // report
  // annotate
  // plot
} // namespace perf
#endif // PERF_IO

#ifndef NTEST
namespace perf::self {
  // test
} // namespace perf::self
#endif // NTEST

#undef PERF_IMPL_EVAL
#undef PERF_IMPL_VERSION
#endif // PERF

#include <iostream>

static auto fizz_buzz = [](int n) {
  if (n % 15 == 0) {
    return "FizzBuzz";
  } else if (n % 3 == 0) {
    return "Fizz";
  } else if (n % 5 == 0) {
    return "Buzz";
  } else {
    return "Unknown";
  }
};

template<class...Ts>
void print(perf::utility::tuple<Ts...> t) {
    ((std::cout << std::string_view(static_cast<Ts>(t).name()) << ":" << std::endl), ...);
}

int main() {
  perf::profiler stat{perf::stat::cpu_time, perf::stat::branch_misses, perf::stat::cycles};
  perf::profiler record{perf::record::cycles, perf::stat::cpu_time, perf::stat::branch_misses, perf::stat::cycles};
  perf::profiler trace{perf::trace::instructions, perf::trace::cycles};
  perf::profiler profiler{stat, record, trace};

  const auto invoke = [&](auto&& fn, auto&&... ts) {
    auto begin = profiler.start();
    perf::core::compiler::prevent_elision(fn(ts...));
    auto end = profiler.stop();
    return perf::utility::tuple(begin, end);
  };

  volatile auto n = 3;
  invoke(fizz_buzz, n);
  invoke(fizz_buzz, 7);

  //auto&& t = profiler[];
  //[&]<class... Ts>(perf::utility::tuple<Ts...>& t) {
    //std::cout << t << std::endl;
  //}(t);

  std::cout << profiler[perf::trace::instructions].size() << std::endl;
  for (const auto& i : profiler[perf::trace::instructions]) {
    std::cout << i.ip << std::endl;
  }
  for (const auto& tsc : profiler[perf::trace::cycles]) {
    std::cout << tsc << std::endl;
  }
  for (const auto& time : profiler[perf::stat::cpu_time]) {
    std::cout << "TIME:" << time << std::endl;
  }
  for (const auto& bm : profiler[perf::stat::branch_misses]) {
    std::cout << std::string_view(profiler[perf::stat::branch_misses].name()) << " " << bm << std::endl;
  }
  for (const auto& c : profiler[perf::stat::cycles]) {
    std::cout << std::string_view(profiler[perf::stat::cycles].name()) << " " << c << std::endl;
  }
  for (const auto& [ip, value] : profiler[perf::record::cycles]) {
    std::cout << ip << " " << value << std::endl;
  }

  perf::analyzer analyzer{}; //perf::mca::cycles
  analyzer << profiler[perf::trace::instructions];
 //  analyzer << std::span(&&begin, &&end);

  auto data = perf::utility::tuple(profiler[], analyzer[]);

#if 0
  perf::runner bench{perf::bench::latency{perf::trace::instructions}};
  bench([]{}, 42);
  for (const auto& [name, data] : bench[perf::trace::instructions]) {
      std::cout << name << std::endl;
      print(data);
  }
#endif

  // perf::profiler profiler{perf::time::cpu, perf::stat::instructions, perf::trace::instructions, perf::record::cycles, perf::record::mem_loads};
  // profiler.start();
  // profiler.stop();

  // perf::analyzer analyzer{perf::mc::assembly, perf::mca::timeline, debug::source, debug::call_stack};
  // analyzer << profiler[perf::trace::instructions];
  // analyzer << region{&&a, &&b}

  // perf::log(tuple(profiler, analyzyer)[time::cpu, timeline, cycles/instructions]);
  // perf::annotate(tuple(analyzer, profiler)[assembly, record::cycles]);

  // perf::runner bench{bench::latency{}};
  // perf::report(bench[time::cpu]);
  // perf::annotate(bench[assemlby, timeline]);
}
