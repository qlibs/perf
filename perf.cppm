// <!--
//
// Copyright (c) 2024-2025 Kris Jusiak <kris@jusiak.net>
//
// | license        | namespace      | guard            | description                        |
// |----------------|----------------|------------------| ---------------------------------- |
// | MIT*           | `perf::*`      | -                | https://opensource.org/license/mit |
// | Apache2:LLVM** | `perf::mca::*` | `PERF_LLVM == 1` | https://llvm.org/LICENSE.txt       |
//
// The MIT License (MIT)*
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
// Apache License v2.0 with LLVM exceptions**
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
module;
#include <perf>
export module perf;

export namespace perf {
  inline namespace utility {
    using perf::verify;                                 /// verifies whether condition is satisfied - aborts if not
    using perf::scoped;                                 /// scoped{.on_entry = ctor, .on_exit = dtor}
    using perf::named;                                  /// named type with run-time name
  } // namespace utility

  namespace mp {                                        /// meta-programming
    using perf::mp::unroll;                             /// repeats fn N times
    using perf::mp::for_each;                           /// for each element
  } // namespace mp

  namespace math::stat {
    using perf::math::stat::min;                        /// min element
    using perf::math::stat::max;                        /// max element
    using perf::math::stat::mean;                       /// mean
    using perf::math::stat::geomean;                    /// geometric mean
    using perf::math::stat::median;                     /// median
    using perf::math::stat::percentile;                 /// percentile
    using perf::math::stat::variance;                   /// variance
    using perf::math::stat::stddev;                     /// standard deviation
    using perf::math::stat::sem;                        /// standard error
    using perf::math::stat::mae;                        /// median absolute errror
    using perf::math::stat::mad;                        /// median absolute deviation
    using perf::math::stat::cv;                         /// coefficient of variation
    using perf::math::stat::z_score;                    /// z-score
    using perf::math::stat::t_score;                    /// t-score
  } // namespace stat

  namespace data {
    using perf::data::sequence;                         /// generates repeated sequence
    using perf::data::range;                            /// generates range of values
    using perf::data::choice;                           /// generates choices with probabilities
    using perf::data::uniform;                          /// generates uniform distrubtion
    using perf::data::normal;                           /// generates normal distrubtion
    using perf::data::take;                             /// generates (lazy) std::vector of generators
  } // namespace data

  namespace dsl {
    using perf::dsl::operator+;                         /// ex. `instructions + cycles`
    using perf::dsl::operator-;                         /// ex. `instructions - cycles`
    using perf::dsl::operator*;                         /// ex. `instructions * cycles`
    using perf::dsl::operator/;                         /// ex. `instructions / cycles`
  } // namespace dsl

  namespace info {
    using perf::info::version;                          /// version of `perf` # (major, minor, patch), ex. '1.0.0'

    namespace compiler {
      using perf::info::compiler::name;                 /// ex. 'clang'
      using perf::info::compiler::version;              /// ex. 20.0.0 { major, minor, patch }
    } // namespace compiler

    namespace cpu {
      using perf::info::cpu::name;                      /// ex. '12th Gen Intel(R) Core(TM) i7-12650H'
      using perf::info::cpu::code_name;                 /// ex. 'alderlake', 'skylake', ...
      using perf::info::cpu::version;                   /// cpu version {family, model, stepping}, ex. '15.0.3'
      using perf::info::cpu::dispatch_width;            /// the number of micro-operations a core can send to its execution units per clock cycle determines the degree of parallel instruction execution
      using perf::info::cpu::features;                  /// features supported by cpu ex. '{avx, avx2, bmi2, ...}'
    } // namespace cpu

    namespace memory {
      using perf::info::memory::level;                  /// enum level{L0, L1, L2, L3, L4}
      using perf::info::memory::icache;                 /// instruction cache info
      using perf::info::memory::dcache;                 /// data cache info
    } // namespace memory

    namespace sys {
      using perf::info::sys::name;                      /// ex. 'linux'
      using perf::info::sys::triple;                    /// ex. 'x86_64-pc-linux-gnu'
      using perf::info::sys::page_size;                 /// ex. 4096 [kb]
    } // namespace sys

    namespace proc::inline self {
      using perf::info::proc::self::name;               /// ex. '/tmp/a.out' # full path
      using perf::info::proc::self::base_address;       /// proc starting memory address, ex. `instruction_pointer - base_address()`
    } // namespace proc::self

    namespace bin {
      using perf::info::bin::addr_to_line;              /// returns `filename:line` from executable/address
      using perf::info::bin::addr_to_fn_name;           /// returns `variable name`` from excutable/address
      using perf::info::bin::addr_to_name;              /// returns `function name` from executable/address
    } // namespace bin
  } // namespace info

  inline namespace core {
    namespace code {
      using perf::code::align;                          /// gnu version of `[[clang::code_align(alignment)]]`
      using perf::code::label;                          /// compile-time code label, ex. `label("loop.begin")`
      using perf::code::labels;                         /// compile-time code labels, ex. `auto&& label = labels["loop.bagin"]`
      using perf::code::tag;                            /// tagged function with code labels
    } // namespace code

    namespace compiler {
      using perf::compiler::prevent_reorder;            /// prevents memory instructions reorder
      using perf::compiler::prevent_elision;            /// prevents elision of given value
      using perf::compiler::is_elided;                  /// returns true if function is elided by the compiler, false otherwise
    } // namespace compiler

    namespace cpu::pipeline {
      using perf::cpu::pipeline::flush;                 /// flushes cpu pipeline (x86: cpuid)
    } // namespace cpu::pipeline

    namespace memory {
      using perf::memory::direction;                    /// enum class direction{up, down}
      using perf::memory::align;                        /// aligns given pointer to specific alignment and offset
      using perf::memory::is_aligned;                   /// returns true if pointer is aligned to specified alignment
      using perf::memory::synchronize;                  /// hardware memory barrier (x86: fence or lock)
      using perf::memory::operation;                    /// enum class operation{read, write}
      using perf::memory::locality;                     /// enum class locality{none, low, moderate, high}
      using perf::memory::prefetch;                     /// prefetches memory from address
      using perf::memory::protection;                   /// enum class protection{read, write, exec}
      using perf::memory::protect;                      /// sets protection on a region of memory
      using perf::memory::pre_fault;
      using perf::memory::lock;                         /// scoped lock for all currently mapped pages

      namespace cache {
        using perf::memory::cache::enable;              /// requires uefi/kernel space
        using perf::memory::cache::disable;             /// requires uefi/kernel space
        using perf::memory::cache::invalidate;          /// requires uefi/kernel space
        using perf::memory::cache::flush;               /// flushes cache region over cacheline size
      } // namespace cache

      namespace heap {
        using perf::memory::heap::pollute;              /// pollutes heap by making n allocations
      } // namespace heap
    } // namespace memory
  } // namespace core

  inline namespace backend {
    #if PERF_LLVM == 1
    using perf::arch;                                   /// arch configuration
    using perf::llvm;                                   /// https://github.com/llvm/llvm-project

    namespace mc {
      using perf::mc::disassembler;

      /// features
      using perf::mc::assembly;                         /// ex. 'mov eax, 1' # perf::arch::syntax::intel
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

      using perf::mc::source;                           /// instruction to source code # requires debug symbols `-g`
    } // namespace mc

    namespace mca {
      using perf::mca::analyzer;

      /// features
      using perf::mca::cycles;
      using perf::mca::instructions;
      using perf::mca::uops;
      using perf::mca::timeline;                        /// produces a detailed report of each instruction’s state transitions through an instruction pipeline
      using perf::mca::resource_pressure;               /// reports the average number of resource cycles consumed every iteration by instructions for every processor resource unit available on the target
      using perf::mca::bottleneck;                      /// correlates increases in backend pressure to dynamic dispatch stalls
    } // namespace mca
    #endif // PERF_LLVM

    /// utilities
    using perf::disassemble;                            /// disassembles region/function/traces
  } // namespace backend

  inline namespace prof {
    using perf::profiler;                               /// profiler{timer{...}, counter{...}, sampler{...}, ...}

    namespace time {
      using perf::time::timer;                          /// timer{steady_clock, cpu, thread, ...}

      /// timers
      using perf::time::steady_clock;                   /// monotonic-time # guranateed to be always increasing
      using perf::time::high_resolution_clock;          /// highest available resolution clock # may not be steady
      #if PERF_LINUX == 1
      using perf::time::cpu;                            /// user-time + sys-time
      using perf::time::thread;                         /// cpu-time for the current thread
      using perf::time::real;                           /// wall-time
      using perf::time::monotonic;                      /// wall-time # guranateed to be always increasing
      #endif // PERF_LINUX
      #if __has_builtin(__builtin_ia32_rdtsc)
      using perf::time::tsc;                            /// time-stamp-counter
      #endif // __builtin_ia32_rdtsc
    } // namespace time

    namespace stat {
      #if PERF_LINUX == 1
      using perf::stat::config;                         /// counter configuration
      using perf::stat::counter;                        /// perf stat -e

      /// events
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
        using perf::stat::ipc;                          /// instruction per cycle (ipc)
        using perf::stat::upc;                          /// uops per cycle (upc)
        using perf::stat::cpi;                          /// cycles per instruction (cpi, inverse of ipc)
        using perf::stat::branch_miss_rate;             /// branch miss rate (branch misses per branch instruction)
        using perf::stat::cache_miss_rate;              /// cache miss rate (cache misses per cache reference)
        using perf::stat::llc_miss_rate;                /// llc miss rate
        using perf::stat::l1_dcache_miss_rate;          /// l1 data cache miss rate
        using perf::stat::l1_icache_miss_rate;          /// l1 instruction cache miss rate
        using perf::stat::dtlb_miss_rate;               /// dtlb miss rate
        using perf::stat::itlb_miss_rate;               /// itlb miss rate
        using perf::stat::frontend_stall_rate;          /// stalled cycles rate (frontend)
        using perf::stat::backend_stall_rate;           /// stalled cycles rate (backend)
        using perf::stat::memory_stall_ratio;           /// memory access rate
        using perf::stat::total_stall_rate;             /// overall stall rate
        using perf::stat::cpu_migration_rate;           /// cpu migrations per cycles
        using perf::stat::context_switch_rate;          /// context switches per cycles
        using perf::stat::page_fault_rate;              /// page fault rate
        using perf::stat::major_fault_rate;             /// page fault rate (major faults per total faults)
        using perf::stat::minor_fault_rate;             /// page fault rate (minor faults per total faults)
      } // namespace metric

      namespace top_down {
        /// level-1
        using perf::stat::top_down::retiring;
        using perf::stat::top_down::bad_speculation;
        using perf::stat::top_down::frontend_bound;
        using perf::stat::top_down::backend_bound;

        /// level-2.retiring
        using perf::stat::top_down::heavy_operations;
        using perf::stat::top_down::light_operations;

        /// level-2.bad_speculation
        using perf::stat::top_down::branch_mispredict;
        using perf::stat::top_down::machine_clears;

        /// level-2.frontend_bound
        using perf::stat::top_down::fetch_latency;
        using perf::stat::top_down::fetch_bandwidth;

        /// level-2.backend_bound
        using perf::stat::top_down::memory_bound;
        using perf::stat::top_down::core_bound;
      } // namespace top_down
      #endif // PERF_LINUX
    } // namespace stat

    namespace record {
      #if PERF_LINUX == 1
      using perf::record::config;                       /// sampler configuration
      using perf::record::sampler;                      /// perf record -e / perf mem record

      /// events
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
      #endif // PERF_LINUX
    } // namespace record

    namespace trace {
      #if PERF_INTEL == 1
      using perf::trace::config;                        /// tracing configuration
      using perf::trace::tracer;                        /// perf record -e intel_pt/

      /// traces
      using perf::trace::instructions;
      using perf::trace::tsc;

      /// utilities
      using perf::trace::trace;                        /// traces function execution
      #endif // PERF_INTEL
    } // namespace trace
  } // namespace prof

  inline namespace engine {
    using perf::name;                                   /// name of `fn(args...)`
    using perf::dataset;                                /// type-safe/type-erased data storage
    using perf::metadata;                               /// type-safe/meta-data storage
    using perf::runner;                                 /// executes functions via runners and stores results in metadata
  } // namespace engine

  namespace bench {
    namespace config {
      using perf::bench::config::iterations;
      using perf::bench::config::samples;
      using perf::bench::config::warmup;
    } // namespace config

    namespace policy {
      using perf::bench::policy::seq;
      using perf::bench::policy::unseq;
      using perf::bench::policy::unroll;
      using perf::bench::policy::par;
      using perf::bench::policy::omp;
    } // namespace policy

    using perf::bench::baseline;
    using perf::bench::latency;                         /// latency is the time it takes for a single operation to complete (ns)
    using perf::bench::throughput;                      /// throughput is the total number of operations or tasks completed in a
                                                        /// given amount of time (op/s)
    /// results
    using perf::bench::operations;
    using perf::bench::samples;
  } // namespace bench

  #if PERF_OUTPUT == 1
  inline namespace output {
    using perf::log;                                    /// logs to the output stream
    using perf::json;                                   /// saves results to the output stream in json format
    using perf::report;                                 /// reports perf benchmark / per operation
    using perf::annotate;                               /// annotates per benchmark / per instruction

    namespace plot {
      using perf::plot::config;                         /// plotting configuration
      using perf::plot::gnuplot;                        /// http://www.gnuplot.info
      using perf::plot::type;                           /// enum class type{point, line, bar, box, err}

      /// plots
      using perf::plot::hist;                           /// histogram
      using perf::plot::bar;                            /// bar with errors
      using perf::plot::box;                            /// box with errors
      using perf::plot::line;                           /// line with errors
      using perf::plot::ecdf;                           /// empirical distribution function

      namespace complexity {
        // bigo
      } // namespace complexity
    } // namespace plot
  } // namespace output
  #endif // PERF_OUTPUT

  #ifndef NTEST
  using perf::test;                                     /// run-time sanity tests
  #endif
} // namespace perf

// -*- mode: c++; -*-
// vim: set filetype=cpp:
