FROM alpine:3.22.0 AS builder

WORKDIR /app

RUN apk update && \
    apk add --no-cache cppcheck make g++

COPY Makefile ./
COPY mk ./mk/
COPY inc ./inc/
COPY src ./src/

RUN make all

FROM alpine:3.22.0

WORKDIR /app

COPY --from=builder /app/webserv .

EXPOSE 443

CMD ["./webserv"]
