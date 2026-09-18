local project = import 'brewkit/project.libsonnet';

local appIDs = [
    'lab01',
    'lab02',
];

project.project(appIDs)
