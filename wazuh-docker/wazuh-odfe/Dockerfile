FROM centos:7

ARG FILEBEAT_VERSION=7.9.1
ARG WAZUH_VERSION=4.0.4-1
ARG TEMPLATE_VERSION="master"
ARG WAZUH_FILEBEAT_MODULE="wazuh-filebeat-0.1.tar.gz"

# Set repositories.
RUN rpm --import https://packages.wazuh.com/key/GPG-KEY-WAZUH

COPY config/wazuh.repo /etc/yum.repos.d/wazuh.repo

RUN yum --enablerepo=updates clean metadata && \
  yum -y install openssl which expect openssh-clients gcc python3-devel python3-pip python3 && yum -y install wazuh-manager-${WAZUH_VERSION} -y && \
  sed -i "s/^enabled=1/enabled=0/" /etc/yum.repos.d/wazuh.repo && \
  yum clean all && rm -rf /var/cache/yum

RUN curl -L -O https://artifacts.elastic.co/downloads/beats/filebeat/filebeat-oss-${FILEBEAT_VERSION}-x86_64.rpm &&\
  rpm -i filebeat-oss-${FILEBEAT_VERSION}-x86_64.rpm && rm -f filebeat-oss-${FILEBEAT_VERSION}-x86_64.rpm

RUN curl -s https://packages.wazuh.com/4.x/filebeat/${WAZUH_FILEBEAT_MODULE} | tar -xvz -C /usr/share/filebeat/module

ARG S6_VERSION="v2.1.0.2"
RUN curl --fail --silent -L https://github.com/just-containers/s6-overlay/releases/download/${S6_VERSION}/s6-overlay-amd64.tar.gz \
    -o /tmp/s6-overlay-amd64.tar.gz && \
    tar xzf /tmp/s6-overlay-amd64.tar.gz -C / --exclude="./bin" && \
    tar xzf /tmp/s6-overlay-amd64.tar.gz -C /usr ./bin && \
    rm  /tmp/s6-overlay-amd64.tar.gz

COPY config/filebeat.yml /etc/filebeat/

RUN chmod go-w /etc/filebeat/filebeat.yml

ADD https://raw.githubusercontent.com/wazuh/wazuh/$TEMPLATE_VERSION/extensions/elasticsearch/7.x/wazuh-template.json /etc/filebeat
RUN chmod go-w /etc/filebeat/wazuh-template.json

COPY config/etc/ /etc/
COPY --chown=root:ossec config/create_user.py /var/ossec/framework/scripts/create_user.py

# Prepare permanent data
# Sync calls are due to https://github.com/docker/docker/issues/9547
COPY config/permanent_data.env config/permanent_data.sh /
RUN chmod 755 /permanent_data.sh && \
    sync && /permanent_data.sh && \
    sync && rm /permanent_data.sh

RUN pip3 install wheel
RUN pip3 install aiohttp[speedups]

COPY lib/socket_writer.py /opt/

# Services ports
EXPOSE 55000/tcp 1514/tcp 1515/tcp 514/udp 1516/tcp 9000/tcp

ENTRYPOINT [ "/init" ]
