#!/bin/bash
#Check all container
containers="comm_app_dev nav_app_dev jam_app_dev sar_app_dev"
for containerName in $containers
do
    exist=`docker inspect --format '{{.State.Running}}' ${containerName}`
    if [ "${exist}" != "true" ]
    then {
        echo "Now start container ${containerName}"
        docker start ${containerName}
    }
    fi

    echo "Container ${containerName} is running. Now start its deploy program..."
    docker exec -id -w /code $containerName  ./deploy.sh
done

