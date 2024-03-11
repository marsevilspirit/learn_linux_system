#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <fcntl.h>

#define PORT_NUM 50000

int main(void)
{
    const int EVENTS_SIZE = 20;
    char buff[1024];

    int socketFd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    sockaddr_in sockAddr{};
    sockAddr.sin_port = htons(PORT_NUM);

    if(bind(socketFd, (sockaddr*) &sockAddr, sizeof(sockAddr)) == -1)
    {
        std::cout << "bind error" << '\n';
        return -1;
    }

    if(listen(socketFd, 10) == -1)
    {
        std::cout << "listen error" << '\n';
        return -1;
    }

    int eFd = epoll_create(1);

    epoll_event epev{};
    epev.events = EPOLLIN;
    epev.data.fd = socketFd;
    epoll_ctl(eFd, EPOLL_CTL_ADD, socketFd, &epev);

    epoll_event events[EVENTS_SIZE];

    while(true)
    {
        int eNum = epoll_wait(eFd, events, EVENTS_SIZE, -1);

        if(eNum == -1)
        {
            std::cout << "epoll_wait" << '\n';
            return -1;
        }

        for(int i = 0; i < eNum; i++)
        {
            if(events[i].data.fd == socketFd)
            {
                sockaddr_in cli_addr{};
                socklen_t length = sizeof(cli_addr);

                int fd = accept(socketFd, (sockaddr*) &cli_addr, &length);

                if(fd > 0)
                {
                    epev.events = EPOLLIN | EPOLLET;
                    epev.data.fd = fd;

                    int flags = fcntl(fd, F_GETFL, 0); 
                    if(flags < 0)
                    {
                        std::cout << "set no block error, fd:" << fd << '\n';
                        continue;
                    }

                    if(fcntl(fd, F_SETFL, flags | O_NONBLOCK) < 0)
                    {
                        std::cout << "set no block error, fd:" << fd << '\n';
                        continue;
                    }

                    epoll_ctl(eFd, EPOLL_CTL_ADD, fd, &epev);
                    std::cout << "client on line fd:" << fd << '\n';
                }
            }
            else 
            {
                if(events[i].events & EPOLLERR ||events[i].events & EPOLLHUP)
                {
                    epoll_ctl(eFd, EPOLL_CTL_DEL, events[i].data.fd, nullptr);
                    std::cout << "client out fd:" << events[i].data.fd << '\n';
                    close(events[i].data.fd);
                }
                else if (events[i].events & EPOLLIN) 
                {
                    int len = read(events[i].data.fd, buff, sizeof(buff)); 
                }
            }
        }
    }
}
