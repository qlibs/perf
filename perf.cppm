// <!--
//
// Copyright (c) 2024-2025 Kris Jusiak <kris@jusiak.net>
//
// | license          | namespace      | guard            | description                        |
// | ---------------- | -------------- | ---------------- | ---------------------------------- |
// | MIT [1]          | `perf::*`      | -                | https://opensource.org/license/mit |
// | Apache2+LLVM [2] | `perf::mca::*` | `PERF_LLVM == 1` | https://llvm.org/LICENSE.txt       |
//
// [1] The MIT License (MIT)
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
// See https://opensource.org/license/mit for license information.
//
// [2] Apache License v2.0 with LLVM exceptions
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
module;
#include <perf>
export module perf;

export namespace perf {
  inline namespace utility {
    using perf::verify;                                 // verifies whether condition is satisfied - aborts if not
    using perf::unroll;                                 // repeats fn N times
    using perf::named;                                  // named type with run-time name
    using perf::scoped;                                 // scoped{.on_entry = ctor, .on_exit = dtor}
  } // namespace utility

  namespace data {
    inline namespace random {
      using perf::data::choice;                         // probabilitity choice
      using perf::data::uniform;                        // uniform distrubution
      using perf::data::normal;                         // normal distrubution
      using perf::data::unpredictable;                  // not elided and not predicted
    } // namespace random

    inline namespace fixed {
      using perf::data::sequence;                       // sequence
      using perf::data::range;                          // range
    } // namespace fixed

    using perf::data::sample;                           // data sampler
  } // namespace data

  namespace metric {
    inline namespace dsl {
      using perf::metric::operator+;                    // ex. `instructions + cycles`
      using perf::metric::operator-;                    // ex. `instructions - cycles`
      using perf::metric::operator*;                    // ex. `instructions * cycles`
      using perf::metric::operator/;                    // ex. `instructions / cycles`
    } // namespace dsl
    inline namespace stat {
      using perf::metric::stat::min;                    // min element
      using perf::metric::stat::max;                    // max element
      using perf::metric::stat::mean;                   // mean
      using perf::metric::stat::geomean;                // geometric mean
      using perf::metric::stat::median;                 // median
      using perf::metric::stat::percentile;             // percentile
      using perf::metric::stat::variance;               // variance
      using perf::metric::stat::stddev;                 // standard deviation (variability)
      using perf::metric::stat::sem;                    // standard error (precision)
      using perf::metric::stat::mae;                    // median absolute errror
      using perf::metric::stat::mad;                    // median absolute deviation
      using perf::metric::stat::cv;                     // coefficient of variation
      using perf::metric::stat::z_score;                // z-score
      using perf::metric::stat::t_score;                // t-score
    } // namespace stat
    using perf::metric::value;
  } // namespace metric::dsl

  namespace info {
    using perf::info::spec;                             // performance specification
    using perf::info::version;                          // version of `perf` # (major, minor, patch), ex. '1.0.0'

    namespace compiler {
      using perf::info::compiler::name;                 // ex. 'clang'
      using perf::info::compiler::version;              // ex. 20.0.0 { major, minor, patch }
    } // namespace compiler

    namespace cpu {
      #if PERF_GNU == 1
      using perf::info::cpu::name;                      // ex. '12th Gen Intel(R) Core(TM) i7-12650H'
      using perf::info::cpu::version;                   // cpu version {family, model, stepping}, ex. '15.0.3'
      #endif
      #if PERF_LLVM == 1
      using perf::info::cpu::code_name;                 // ex. 'alderlake', 'skylake', ...
      using perf::info::cpu::dispatch_width;            // the number of micro-operations a core can send to its execution units per clock cycle determines the degree of parallel instruction execution
      using perf::info::cpu::features;                  // features supported by cpu ex. '{avx, avx2, bmi2, ...}'
      #endif
    } // namespace cpu

    namespace memory {
      #if PERF_LINUX == 1
      using perf::info::memory::level;                  // enum level{L0, L1, L2, L3, L4}
      using perf::info::memory::icache;                 // instruction cache info
      using perf::info::memory::dcache;                 // data cache info
      using perf::info::memory::peak_rss;               // maximum resident set size
      #endif
    } // namespace memory

    namespace sys {
      using perf::info::sys::name;                      // ex. 'linux'
      using perf::info::sys::page_size;                 // ex. 4096 [kb]
      #if PERF_LLVM == 1
      using perf::info::sys::triple;                    // ex. 'x86_64-pc-linux-gnu'
      #endif
    } // namespace sys

    namespace proc::inline self {
      #if PERF_LINUX == 1
      using perf::info::proc::self::name;               // ex. '/tmp/a.out' # full path
      using perf::info::proc::self::base_address;       // proc starting memory address, ex. `instruction_pointer - base_address()`
      #endif
    } // namespace proc::self

    namespace bin {
      #if PERF_LLVM == 1
      using perf::info::bin::addr_to_line;              // returns `filename:line` from executable/address
      using perf::info::bin::addr_to_fn_name;           // returns `variable name` from excutable/address
      using perf::info::bin::addr_to_name;              // returns `function name` from executable/address
      #endif
    } // namespace bin
  } // namespace info

  inline namespace core {
    namespace code {
      #if PERF_GNU == 1
      using perf::code::align;                          // gnu version of `[[clang::code_align(alignment)]]`
      using perf::code::label;                          // global compile-time code label, ex. `label<"loop.begin">()`
      using perf::code::labels;                         // global compile-time code labels, ex. `auto&& label = labels["loop.bagin"]`
      #endif
    } // namespace code

    namespace compiler {
      #if PERF_GNU == 1
      using perf::compiler::prevent_reorder;            // prevents memory instructions reorder
      using perf::compiler::prevent_elision;            // prevents elision of given value
      using perf::compiler::is_elided;                  // returns true if function is elided by the compiler, false otherwise
      #endif
    } // namespace compiler

    namespace cpu::pipeline {
      #if PERF_GNU == 1 and defined(__x86_64__)
      using perf::cpu::pipeline::flush;                 // flushes cpu pipeline (x86: cpuid)
      #endif
    } // namespace cpu::pipeline

    namespace memory {
      using perf::memory::direction;                    // enum class direction{up, down}
      using perf::memory::align;                        // aligns given pointer to specific alignment and offset
      using perf::memory::is_aligned;                   // returns true if pointer is aligned to specified alignment
      #if PERF_GNU == 1 and defined(__x86_64__)
      using perf::memory::synchronize;                  // hardware memory barrier (x86: fence or lock)
      #endif
      #if __has_builtin(__builtin_prefetch)
      using perf::memory::operation;                    // enum class operation{read, write}
      using perf::memory::locality;                     // enum class locality{none, low, moderate, high}
      using perf::memory::prefetch;                     // prefetches memory from address
      #endif
      #if PERF_LINUX == 1
      using perf::memory::protection;                   // enum class protection{read, write, exec}
      using perf::memory::protect;                      // sets protection on a region of memory
      using perf::memory::pre_fault;                    // touches all pages used by data
      using perf::memory::lock;                         // scoped lock for all currently mapped pages
      #endif
      using perf::memory::pollute;                      // pollutes memory by making allocations

      namespace cache {
        #if PERF_GNU == 1
        using perf::memory::cache::flush;               // clears all cache lines used by data
        #endif
      } // namespace cache
    } // namespace memory
  } // namespace core

  inline namespace backend {
    #if PERF_LLVM == 1
    using perf::arch;                                   // march configuration
    using perf::analyzer;                               // analyzer{assembly, source, timeline, ...}

    namespace mc {
      using perf::mc::assembly;                         // ex. 'mov eax, 1' # perf::arch::syntax::intel
      using perf::mc::address;
      using perf::mc::encoding;
      using perf::mc::size;
      using perf::mc::uops;
      using perf::mc::latency;
      using perf::mc::rthroughput;
      using perf::mc::may_load;
      using perf::mc::may_store;
      using perf::mc::has_side_effects;

      namespace branch {
        using perf::mc::branch::is_conditional;
        using perf::mc::branch::is_unconditional;
        using perf::mc::branch::is_indirect;
        using perf::mc::branch::is_call;
        using perf::mc::branch::is_ret;
      } // namespace branch

      using perf::mc::source;                           // instruction to source code # requires debug symbols `-g`
    } // namespace mc

    namespace mca {
      namespace stat {
        using perf::mca::stat::cycles;
        using perf::mca::stat::instructions;
        using perf::mca::stat::uops;
      } // namespace stat

      using perf::mca::timeline;                        // produces a detailed report of each instruction’s state transitions through an instruction pipeline
      using perf::mca::resource_pressure;               // reports the average number of resource cycles consumed every iteration by instructions for every processor resource unit available on the target
      using perf::mca::bottleneck;                      // correlates increases in backend pressure to dynamic dispatch stalls
    } // namespace mca
    #endif
  } // namespace backend

  inline namespace prof {
    using perf::profiler;                               // profiler{timer{...}, counter{...}, sampler{...}, ...}

    namespace time {
      using perf::time::timer;                          // timer{steady_clock, cpu, thread, ...}

      inline namespace total {
        using perf::time::steady_clock;                 // monotonic-time # guranateed to be always increasing
        using perf::time::high_resolution_clock;        // highest available resolution clock # may not be steady
        #if PERF_LINUX == 1
        using perf::time::cpu;                          // user-time + sys-time
        using perf::time::thread;                       // cpu-time for the current thread
        using perf::time::real;                         // wall-time
        using perf::time::monotonic;                    // wall-time # guranateed to be always increasing
        #endif
        #if __has_builtin(__builtin_ia32_rdtsc)
        using perf::time::tsc;                          // time-stamp-counter
        #endif
        inline namespace metric {
          using perf::time::metric::seconds;
        } // namespace metric
      } // namespace total
    } // namespace time

    namespace stat {
      #if PERF_LINUX == 1
      using perf::stat::config;                         // counter configuration
      using perf::stat::counter;                        // perf stat -e

      inline namespace event {
        using perf::stat::cpu_clock;
        using perf::stat::task_clock;
        using perf::stat::faults;
        using perf::stat::page_faults;
        using perf::stat::major_faults;
        using perf::stat::minor_faults;
        using perf::stat::alignment_faults;
        using perf::stat::emulation_faults;
        using perf::stat::context_switches;
        using perf::stat::cgroup_switches;
        using perf::stat::cpu_migrations;
        using perf::stat::migrations;
        using perf::stat::instructions;
        using perf::stat::cycles;
        using perf::stat::stalled_cycles_backend;
        using perf::stat::idle_cycles_backend;
        using perf::stat::stalled_cycles_frontend;
        using perf::stat::idle_cycles_frontend;
        using perf::stat::branches;
        using perf::stat::branch_misses;
        using perf::stat::branch_instructions;
        using perf::stat::cache_references;
        using perf::stat::cache_misses;
        using perf::stat::llc_misses;
        using perf::stat::l1_misses;
        using perf::stat::l1_dcache_loads;
        using perf::stat::l1_dcache_load_misses;
        using perf::stat::l1_icache_loads;
        using perf::stat::l1_icache_load_misses;
        using perf::stat::dtlb_loads;
        using perf::stat::dtlb_load_misses;
        using perf::stat::itlb_loads;
        using perf::stat::itlb_load_misses;

        inline namespace metric {
          using perf::stat::ipc;                        // instruction per cycle (ipc)
          using perf::stat::cpi;                        // cycles per instruction (cpi, inverse of ipc)
          using perf::stat::branch_miss_rate;           // branch miss rate (branch misses per branch instruction)
          using perf::stat::cache_miss_rate;            // cache miss rate (cache misses per cache reference)
          using perf::stat::llc_miss_rate;              // llc miss rate
          using perf::stat::l1_dcache_miss_rate;        // l1 data cache miss rate
          using perf::stat::l1_icache_miss_rate;        // l1 instruction cache miss rate
          using perf::stat::dtlb_miss_rate;             // dtlb miss rate
          using perf::stat::itlb_miss_rate;             // itlb miss rate
          using perf::stat::frontend_stall_rate;        // stalled cycles rate (frontend)
          using perf::stat::backend_stall_rate;         // stalled cycles rate (backend)
          using perf::stat::memory_stall_ratio;         // memory access rate
          using perf::stat::total_stall_rate;           // overall stall rate
          using perf::stat::cpu_migration_rate;         // cpu migrations per cycles
          using perf::stat::context_switch_rate;        // context switches per cycles
          using perf::stat::page_fault_rate;            // page fault rate
          using perf::stat::major_fault_rate;           // page fault rate (major faults per total faults)
          using perf::stat::minor_fault_rate;           // page fault rate (minor faults per total faults)
        } // namespace metric

        namespace top_down {
          using perf::stat::top_down::retiring;
          using perf::stat::top_down::heavy_operations;
          using perf::stat::top_down::light_operations;

          using perf::stat::top_down::bad_speculation;
          using perf::stat::top_down::branch_mispredict;
          using perf::stat::top_down::machine_clears;

          using perf::stat::top_down::frontend_bound;
          using perf::stat::top_down::fetch_latency;
          using perf::stat::top_down::fetch_bandwidth;

          using perf::stat::top_down::backend_bound;
          using perf::stat::top_down::memory_bound;
          using perf::stat::top_down::core_bound;
        } // namespace top_down
      } // namespace event
      #endif // PERF_LINUX
    } // namespace stat

    namespace record {
      #if PERF_LINUX == 1
      using perf::record::config;                       // sampler configuration
      using perf::record::sampler;                      // perf record -e / perf mem record

      inline namespace event {
        using perf::record::cpu_clock;
        using perf::record::task_clock;
        using perf::record::page_faults;
        using perf::record::faults;
        using perf::record::major_faults;
        using perf::record::minor_faults;
        using perf::record::alignment_faults;
        using perf::record::emulation_faults;
        using perf::record::context_switches;
        using perf::record::cgroup_switches;
        using perf::record::cpu_migrations;
        using perf::record::migrations;
        using perf::record::cycles;
        using perf::record::instructions;
        using perf::record::branch_misses;
        using perf::record::bus_cycles;
        using perf::record::cache_misses;
        using perf::record::cache_references;
        using perf::record::branches;
        using perf::record::branch_instructions;
        using perf::record::stalled_cycles_backend;
        using perf::record::idle_cycles_backend;
        using perf::record::stalled_cycles_frontend;
        using perf::record::idle_cycles_frontend;
        using perf::record::llc_misses;
        using perf::record::l1_misses;
        using perf::record::l1_dcache_loads;
        using perf::record::l1_dcache_load_misses;
        using perf::record::l1_icache_loads;
        using perf::record::l1_icache_load_misses;
        using perf::record::dtlb_loads;
        using perf::record::dtlb_load_misses;
        using perf::record::itlb_loads;
        using perf::record::itlb_load_misses;
        using perf::record::mem_loads;
        using perf::record::mem_stores;
      } // namespace event
      #endif
    } // namespace record

    namespace trace {
      #if PERF_LINUX == 1 and PERF_INTEL == 1
      using perf::trace::config;                        // tracing configuration
      using perf::trace::tracer;                        // perf record -e intel_pt/

      inline namespace event {
        using perf::trace::instructions;
        using perf::trace::tsc;
      } // namespace event
      #endif
    } // namespace trace
  } // namespace prof

  inline namespace engine {
    using perf::name;                                   // name of `fn(args...)`
    using perf::dataset;                                // type-safe/type-erased data storage
    using perf::metadata;                               // type-safe/meta-data storage
    using perf::runner;                                 // executes functions via runners and stores results in metadata
  } // namespace engine

  namespace bench {
    namespace config {
      using perf::bench::config::iterations;
      using perf::bench::config::samples;
    } // namespace config

    namespace policy {
      using perf::bench::policy::seq;
      using perf::bench::policy::unseq;
      using perf::bench::policy::unroll;
      using perf::bench::policy::par;
      using perf::bench::policy::omp;
      using perf::bench::policy::cuda;
    } // namespace policy

    using perf::bench::baseline;
    using perf::bench::latency;                         // latency is the time it takes for a single operation to complete (ns)
    using perf::bench::throughput;                      // throughput is the total number of operations or tasks completed in a
                                                        // given amount of time (op/s)
    inline namespace stat {
      using perf::bench::operations;
      using perf::bench::samples;
    } // namespace stat
  } // namespace bench

  #if PERF_IO == 1
  inline namespace io {
    using enum perf::misc::split;

    using perf::log;                                    // logs to the output stream
    using perf::report;                                 // reports perf benchmark / per operation
    using perf::annotate;                               // annotates per benchmark / per instruction
    using perf::json;                                   // saves results to the output stream in json format

    namespace plot {
      using perf::plot::kind;                           // enum class kind{point, line, bar, box, err}
      using perf::plot::config;                         // plotting configuration
      using perf::plot::gnuplot;                        // http://www.gnuplot.info

      using perf::plot::hist;                           // histogram
      using perf::plot::bar;                            // bar with errors
      using perf::plot::box;                            // box with errors
      using perf::plot::line;                           // line with errors
      using perf::plot::ecdf;                           // empirical distribution function
    } // namespace plot
  } // namespace io
  #endif

  #ifndef NTEST
  inline namespace self {
    using perf::self::test;                             // run-time sanity tests
  } // namespace self
  #endif
} // namespace perf

// -*- mode: c++; -*-
// vim: set filetype=cpp:
