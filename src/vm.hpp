#pragma once

extern "C" void tech_paws_vm_log_trace(char const* message);

extern "C" void tech_paws_vm_log_error(char const* message);

extern "C" void tech_paws_vm_log_warn(char const* message);

extern "C" void tech_paws_vm_log_debug(char const* message);

extern "C" void tech_paws_vm_log_info(char const* message);
