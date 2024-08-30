// <!--
//
// Copyright (c) 2024-2025 Kris Jusiak <kris@jusiak.net>
//
// | license        | namespace      | guard            |
// |----------------|----------------|------------------|
// | MIT*           | `perf::*`      | -                |
// | Apache2:LLVM** | `perf::mca::*` | `PERF_LLVM == 1` |
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
    using perf::verify;
    using perf::scoped;
    using perf::overloaded;
    using perf::fixed_named;
    using perf::named;
  } // namespace utility

  namespace mp {
    using perf::mp::unroll;
    using perf::mp::for_each;
  } // namespace mp

  namespace math::stat {
    using perf::math::stat::min;
    using perf::math::stat::max;
    using perf::math::stat::mean;
    using perf::math::stat::geomean;
    using perf::math::stat::median;
    using perf::math::stat::percentile;
    using perf::math::stat::variance;
    using perf::math::stat::stddev;
    using perf::math::stat::sem;
    using perf::math::stat::mae;
    using perf::math::stat::mad;
    using perf::math::stat::cv;
    using perf::math::stat::z_score;
    using perf::math::stat::t_score;
  } // namespace stat

  namespace data {
    using perf::data::repeat;
    using perf::data::range;
    using perf::data::choice;
    using perf::data::uniform;
    using perf::data::normal;
    using perf::data::take;
  } // namespace data

  namespace info {
    /**
     * PERF version
     */
    using perf::info::version;

    namespace compiler {
      using perf::info::compiler::name;
      using perf::info::compiler::version;
    } // namespace compiler

    namespace cpu {
      using perf::info::cpu::name;
      using perf::info::cpu::code_name;
      using perf::info::cpu::version;
      using perf::info::cpu::dispatch_width;
      using perf::info::cpu::features;
    } // namespace cpu

    namespace memory {
      using perf::info::memory::level;
      using perf::info::memory::icache;
      using perf::info::memory::dcache;
    } // namespace memory

    namespace sys {
      using perf::info::sys::name;
      using perf::info::sys::triple;
      using perf::info::sys::page_size;
    } // namespace sys

    namespace proc::inline self {
      using perf::info::proc::self::name;
      using perf::info::proc::self::base_address;
    } // namespace proc::self

    namespace bin {
      /**
       * Converts address into a file name:line number
       */
      using perf::info::bin::addr_to_line;

      /**
       * Converts address into a function name
       */
      using perf::info::bin::addr_to_fn_name;

      /**
       * Converts address into a name
       */
      using perf::info::bin::addr_to_name;
    } // namespace bin
  } // namespace info

  inline namespace core {
    namespace code {
      /**
       * gnu version of `[[clang::code_align(alignment)]]`
       */
      using perf::code::align;

      /**
       * compile-time code label
       */
      using perf::code::label;

      /**
       * loads compile-time code labels
       */
      using perf::code::labels;
    } // namespace code

    namespace compiler {
      /**
       * prevents memory instructions reorder
       */
      using perf::compiler::prevent_reorder;

      /**
       * prevents elision of given value
       */
      using perf::compiler::prevent_elision;

      /**
       * returns true if given function is elided by the compiler, false otherwise
       */
      using perf::compiler::is_elided;
    } // namespace compiler

    namespace cpu::pipeline {
      using perf::cpu::pipeline::flush;
    } // namespace cpu::pipeline

    namespace memory {
      /**
       * aligns given pointer to specific alignment and offset
       */
      using perf::memory::direction;
      using perf::memory::align;

      /**
       * returns true if given pointer is aligned to specified alignment
       */
      using perf::memory::is_aligned;

      /**
       * hardware memory barrier (x86: fence or lock)
       */
      using perf::memory::fence;

      /**
       * Prefetches memory from address
       */
      using perf::memory::operation;
      using perf::memory::locality;
      using perf::memory::prefetch;

      /**
       * Sets protection on a region of memory
       */
      using perf::memory::prot;
      using perf::memory::protect;

      using perf::memory::pre_fault;
      using perf::memory::lock;

      namespace cache {
        using perf::memory::cache::flush;
      } // namespace cache

      namespace heap {
        /**
         * pollutes heap by making n allocations
         */
        using perf::memory::heap::pollute;
      } // namespace heap
    } // namespace memory
  } // namespace core

  inline namespace backend {
    using perf::arch;
    using perf::llvm;

    namespace mc {
      using perf::mc::disassemble;
      using perf::mc::instructions;

      inline namespace info {
        using perf::mc::assembly;
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
      } // namespace info

      /**
       * Instruction to source code # line (requires debug symbols `-g`)
       */
      using perf::mc::source;
    } // namespace mc

    namespace mca {
      using perf::mca::timeline;
      using perf::mca::resource_pressure;
      using perf::mca::bottleneck;
    } // namespace mca
  } // namespace backend

  inline namespace prof {
    using perf::profiler_like;
    using perf::profiler;

    namespace time {
      using perf::time::timer;

      /// monotonic-time / guranateed to be always increasing
      using perf::time::steady_clock;

      /// user-time + sys-time
      using perf::time::cpu;

      /// cpu-time for the current thread
      using perf::time::thread;

      /// wall-time
      using perf::time::real;

      /// wall-time / guranateed to be always increasing
      using perf::time::monotonic;

      /// time-stamp-counter # https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#text=rdtsc
      using perf::time::tsc;
    } // namespace time

    namespace stat {
      using perf::stat::config;

      /**
       * `perf stat -e`
       */
      using perf::stat::counter;

      /**
       * events
       */
      using perf::stat::cpu_clock;
      using perf::stat::task_clock;
      using perf::stat::page_faults;
      using perf::stat::faults;
      using perf::stat::major_faults;
      using perf::stat::minor_faults;
      using perf::stat::alignment_faults;
      using perf::stat::emulation_faults;
      using perf::stat::context_switches;
      using perf::stat::bpf_output;
      using perf::stat::cgroup_switches;
      using perf::stat::cpu_migrations;
      using perf::stat::migrations;
      using perf::stat::cycles;
      using perf::stat::instructions;
      using perf::stat::branch_misses;
      using perf::stat::bus_cycles;
      using perf::stat::cache_misses;
      using perf::stat::cache_references;
      using perf::stat::branches;
      using perf::stat::branch_instructions;
      using perf::stat::stalled_cycles_backend;
      using perf::stat::idle_cycles_backend;
      using perf::stat::stalled_cycles_frontend;
      using perf::stat::idle_cycles_frontend;
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
        /// instruction per cycle (ipc)
        using perf::stat::ipc;

        /// cycles per instruction (cpi, inverse of ipc)
        using perf::stat::cpi;

        /// branch miss rate (branch misses per branch instruction)
        using perf::stat::branch_miss_rate;

        /// cache miss rate (cache misses per cache reference)
        using perf::stat::cache_miss_rate;

         /// llc miss rate
        using perf::stat::llc_miss_rate;

        /// l1 data cache miss rate
        using perf::stat::l1_dcache_miss_rate;

        /// l1 instruction cache miss rate
        using perf::stat::l1_icache_miss_rate;

        /// dtlb miss rate
        using perf::stat::dtlb_miss_rate;

        /// itlb miss rate
        using perf::stat::itlb_miss_rate;

        /// stalled cycles rate (frontend)
        using perf::stat::frontend_stall_rate;

        /// stalled cycles rate (backend)
        using perf::stat::backend_stall_rate;

        /// memory access rate
        using perf::stat::memory_stall_ratio;

        /// overall stall rate
        using perf::stat::total_stall_rate;

         /// cpu migrations per cycles
        using perf::stat::cpu_migration_rate;

        /// context switches per cycles
        using perf::stat::context_switch_rate;

        /// page fault rate
        using perf::stat::page_fault_rate;

        /// page fault rate (major faults per total faults)
        using perf::stat::major_fault_rate;

        /// page fault rate (minor faults per total faults)
        using perf::stat::minor_fault_rate;
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
    } // namespace stat

    namespace record {
      using perf::record::config;

      /**
       * `perf record -e`
       * `perf mem`
       * `perf record -b` / last branch record (lbr)
       */
      using perf::record::sampler;

      /**
       * events
       */
      using perf::record::cpu_clock;
      using perf::record::task_clock;
      using perf::record::page_faults;
      using perf::record::faults;
      using perf::record::major_faults;
      using perf::record::minor_faults;
      using perf::record::alignment_faults;
      using perf::record::emulation_faults;
      using perf::record::context_switches;
      using perf::record::bpf_output;
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

      namespace memory {
        using perf::record::memory::loads;
        using perf::record::memory::stores;
      } // namespace memory

      namespace branch {
        using perf::record::branch::any;
        using perf::record::branch::jmp;
        using perf::record::branch::call;
        using perf::record::branch::ret;
      } // namespace branch
    } // namespace record

    namespace trace {
      using perf::trace::config;

      /**
       * `perf record -e intel_pt/`
       */
      using perf::trace::tracer;

      /**
       * traces
       */
      using perf::trace::cyc; // cycles
      using perf::trace::tsc; // time-stamp-counter

      /**
       * trace function execution
       */
      using perf::trace::trace;
      using perf::trace::instructions;
    } // namespace trace

    namespace tool {
      /**
       * third-party profiling tools # require external command
       */
      using namespace perf::tool;
    } // namespace tool
  } // namespace prof

  namespace bench {
    using perf::bench::cold;
    using perf::bench::warm;
    using perf::bench::latency;
    using perf::bench::throughput;
    using perf::bench::iterations;
    using perf::bench::samples;
  } // namespace bench

  inline namespace out {
    using perf::log;
    using perf::report;
    using perf::annotate;
    using perf::json;
    using enum perf::layout::split;
    namespace plot {
      using perf::plot::hist;
      using perf::plot::bar;
      using perf::plot::box;
      using perf::plot::ecdf;
      using perf::plot::line;
    } // namespace plot
  } // namespace out

  inline namespace utility {
    using perf::dataset;
    using perf::engine;
    using perf::runner;
    namespace dsl {
      using perf::dsl::operator+;
      using perf::dsl::operator-;
      using perf::dsl::operator*;
      using perf::dsl::operator/;
    } // namespace dsl
  } // namespace utility

  namespace test {
    /**
     * sanity checks
     */
    using perf::test::run;
  } // namespace test
} // namespace perf

// -*- mode: c++; -*-
// vim: set filetype=cpp:
