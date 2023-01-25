#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

void	perr(char *str)
{
	while (*str)
		write(2, str++, 1);
}

int	cd(char **av, int i)
{
	if (i != 2)
		return perr("error: cd: bad arguments\n"), 1;
	else if (chdir(av[1]) == -1)
		return perr("error: cd: cannot change directory to "), perr(av[1]), perr("\n"), 1;
	return 0;
}

int	exec(char **av, int i, char **envp)
{
	int			fd[2], status = 0, p = (av[i] && !strcmp(av[i], "|"));
	static int	pid;

	if (p)
		if (pipe(fd) == -1)
			return perr("error: fatal\n"), 1;
	pid = fork();
	if (pid == -1){
		if (p)
			close(fd[0]), close(fd[1]);
		return perr("error: fatal\n"), 1;
	}
	else if (!pid){
		if (p)
			if (dup2(fd[1], 1) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1)
				perr("error: fatal\n"), exit (1);
		av[i] = NULL;
		execve(av[0], av, envp);
		perr("error: cannot execute "), perr(av[0]), perr("\n"), exit(1);
	}
	if (p)
		if (dup2(fd[0], 0) == -1 || close(fd[0]) == -1 || close(fd[1]) == -1)
				return perr("error: fatal\n"), 1;
	if (!p){
		waitpid(pid, &status, 0);
		while (waitpid(-1, 0, 0) != -1)
			continue;
	}
	return status;
}

int	main(int ac, char **av, char **envp)
{
	int	i = 0, status = 0;

	(void)ac;
	while(av[i] && av[i + 1]){
		av = &av[i + 1];
		i = 0;
		while(av[i] && strcmp(av[i], "|") && strcmp(av[i], ";"))
			i++;
		if (!strcmp(av[0], "cd"))
			status = cd(av, i);
		else if (i)
			status = exec(av, i, envp);
	}
	return status > 255 ? status /= 255 : status;
}
