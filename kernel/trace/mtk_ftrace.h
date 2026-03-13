/*
 * Copyright (C) 2015 MediaTek Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 */

#undef TRACE_SYSTEM
#define TRACE_SYSTEM mtk_ftrace

#if !defined(_TRACE_MTK_FTRACE_H) || defined(TRACE_HEADER_MULTI_READ)
#define _TRACE_MTK_FTRACE_H

#include <linux/tracepoint.h>
#include <linux/string.h>
#include <linux/seq_file.h>

TRACE_EVENT(tracing_on,
	TP_PROTO(int on, unsigned long ip),
	TP_ARGS(on, ip),
	TP_STRUCT__entry(
		__field(int, on)
		__field(unsigned long, ip)
	),
	TP_fast_assign(
		__entry->on = on;
		__entry->ip = ip;
	),
	TP_printk("ftrace is %s caller=%ps",
		  __entry->on ? "enabled" : "disabled",
		  (void *)__entry->ip)
);

#ifdef CONFIG_MTK_KERNEL_MARKER
void trace_begin(char *name);
void trace_counter(char *name, int count);
void trace_end(void);
#else
#define trace_begin(name)
#define trace_counter(name, count)
#define trace_end()
#endif

struct trace_array;
extern bool ring_buffer_expanded;
ssize_t tracing_resize_ring_buffer(struct trace_array *tr,
				   unsigned long size, int cpu_id);

#ifdef CONFIG_MTK_SCHED_TRACERS
struct trace_buffer;
void print_enabled_events(struct trace_buffer *buf, struct seq_file *m);
void update_buf_size(unsigned long size);
bool boot_ftrace_check(unsigned long trace_en);
#ifdef CONFIG_MTPROF
extern int boot_finish;
#endif
#else
#define print_enabled_events(b, m)
#endif /* CONFIG_TRACING && CONFIG_MTK_SCHED_TRACERS */

#endif /* _TRACE_MTK_FTRACE_H */

#undef TRACE_INCLUDE_PATH
#undef TRACE_INCLUDE_FILE
#define TRACE_INCLUDE_PATH .
#define TRACE_INCLUDE_FILE mtk_ftrace

#include <trace/define_trace.h>
