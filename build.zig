const std = @import("std");

const targets: []const std.Target.Query = &.{
    .{},
};

const name = "ccollections";

pub fn build(b: *std.Build) void {
    const optimize = b.standardOptimizeOption(.{
        .preferred_optimize_mode = .ReleaseSmall,
    });

    for (targets) |t| {
        const libStatic = b.addStaticLibrary(.{
            .name = name,
            .target = b.resolveTargetQuery(t),
            .optimize = optimize,
        });
        libStatic.linkLibC();
        libStatic.addCSourceFiles(.{ .files = &.{
            "src/array_list.c",
            "src/assertations.c",
            "src/linked_list.c",
            "src/list.c",
            "src/binary_tree.c",
            "src/tree_set.c",
        }, .flags = &.{} });

        const libDynamic = b.addSharedLibrary(.{
            .name = name,
            .target = b.resolveTargetQuery(t),
            .optimize = optimize,
        });
        libDynamic.linkLibC();
        libDynamic.addCSourceFiles(.{ .files = &.{
            "src/array_list.c",
            "src/assertations.c",
            "src/linked_list.c",
            "src/list.c",
            "src/binary_tree.c",
            "src/tree_set.c",
        }, .flags = &.{} });

        const exe = b.addExecutable(.{
            .name = name,
            .target = b.resolveTargetQuery(t),
            .optimize = optimize,
        });
        exe.linkLibC();
        exe.linkLibrary(libDynamic);
        exe.addCSourceFiles(.{ .files = &.{
            "tests.c",
        }, .flags = &.{} });

        b.installArtifact(libStatic);
        b.installArtifact(libDynamic);
        b.installArtifact(exe);
    }
}
