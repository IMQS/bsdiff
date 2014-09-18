#pragma once

#define ERR_BUFF_SIZE 4096

void err_g(int show_sys_err, int exitcode, const char* msg, ...)
{
	char buff[ERR_BUFF_SIZE] = "";
	if (show_sys_err)
	{
		//_strerror_s(buff, ERR_BUFF_SIZE);
		//fputs(buff, stdout);
		//fputs(": ", stdout);
	}
	va_list va;
	va_start( va, msg );
	int r = vsnprintf( buff, ERR_BUFF_SIZE, msg, va );
	va_end( va );
	buff[ERR_BUFF_SIZE - 1] = 0;
	if (r < ERR_BUFF_SIZE)
	{
		if (show_sys_err)
			perror(buff);
		else
			fputs(buff, stderr);
	}
	exit(exitcode);
}

#define err(exit_code, msg, ...)  err_g(1, exit_code, msg, __VA_ARGS__)
#define errx(exit_code, msg, ...) err_g(0, exit_code, msg, __VA_ARGS__)

#undef ERR_BUFF_SIZE
