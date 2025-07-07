const std = @import("std");

const targets: []const std.Target.Query = &.{
    .{},
};

pub fn build(b: *std.Build) void {
    const optimize = b.standardOptimizeOption(.{
        .preferred_optimize_mode = .ReleaseSmall,
    });

    for (targets) |t| {
        const exe = b.addExecutable(.{
            .name = "collections",
            .target = b.resolveTargetQuery(t),
            .optimize = optimize,
        });
        exe.linkLibC();
        exe.addCSourceFiles(.{ .files = &.{
            "src/array_list.c",
            "src/assertations.c",
            "src/linked_list.c",
            "src/binary_tree.c",
            "tests.c",
        }, .flags = &.{} });

        b.installArtifact(exe);
    }
}
